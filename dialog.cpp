#include "dialog.h"
#include "ui_dialog.h"
#include "dialogeventhandlers.h"

#include <array>

#include <QTimer>
#include <QOpenGLFunctions>
#include <QWidget>
#include <QQuaternion>
#include <QOpenGLTexture>
#include <QImage>

#include <QDebug>

#include <glm/glm.hpp>

constexpr float CAMERA_SPEED = 3.0f;

Dialog::Dialog(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::Dialog)
    , m_view()
    , m_cubeIndices(QOpenGLBuffer::IndexBuffer)
    , m_sphere(100, 100)
    , m_eventHandler(new EventHandler::NoopEventHandler())
{

    //make the window appear
    ui->setupUi(this);

    //setup timer
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    m_timer->start(1000 / 60);
}

Dialog::~Dialog()
{
    delete ui;
    delete m_timer;
}


// Use C++11 raw string literals for GLSL shader source code

static const char *vertexShaderSourceCore = R"(
    #version 120
    uniform mat4 projMatrix;
    uniform mat4 mvMatrix;

    attribute vec4 vertex;
    attribute vec2 in_texcoord;

    varying vec2 v_texcoord;

    void main() {
       gl_Position = projMatrix * mvMatrix * vertex;
       v_texcoord = in_texcoord;
    }
)";

static const char *fragmentShaderSourceCore = R"(
    #version 120
    uniform sampler2D texture;

    varying vec2 v_texcoord;

    void main() {
       gl_FragColor = texture2D(texture, v_texcoord);
    }
)";

bool Dialog::event(QEvent* event)
{
    return m_eventHandler->handleEvent(event) || QOpenGLWidget::event(event);
}

void Dialog::initializeGL()
{

    m_view.setToIdentity();
    m_view.translate(0, 0, -3);

    glClearColor(0, 0, 0, 1);

    m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);

    m_program.link();

    m_program.bind();

    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);


    const std::vector<VertexData>& vertices = m_sphere.getVertexData();
    const std::vector<unsigned short>& vertexIndices = m_sphere.getIndices();

    static_assert(sizeof(VertexData) == 5*sizeof(float), "VertexData layout not as expected");

    // Setup our vertex buffer object.
    m_cubeVertices.create();
    m_cubeVertices.bind();
    m_cubeVertices.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

    m_cubeIndices.create();
    m_cubeIndices.bind();
    m_cubeIndices.allocate(vertexIndices.data(), vertexIndices.size() * sizeof(GLushort));

    // Tell OpenGL programmable pipeline how to locate vertex position data
    m_program.enableAttributeArray("vertex");
    m_program.setAttributeBuffer("vertex", GL_FLOAT, 0, 3, sizeof(VertexData));

    m_program.enableAttributeArray("in_texcoord");
    m_program.setAttributeBuffer("in_texcoord", GL_FLOAT, sizeof(glm::vec3), 2, sizeof(VertexData));

    m_program.release();

    // Load textures
    m_texture = new QOpenGLTexture(QImage("./map1.png").mirrored(true, true));
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Add renderer event chain
    m_eventHandler.reset(new KeyEventHandler(*this));
    m_eventHandler->chain(std::make_shared<KeyEventPan>(*this))
        ->chain(std::make_shared<MouseWheelEventZoom>(*this));
}

void Dialog::paintGL()
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(this->width()) / this->height(), 0.01f, 100.0f);

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);

    m_vao.bind();

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program.bind();
    m_program.setUniformValue("projMatrix", m_proj);
    m_program.setUniformValue("mvMatrix", m_view * m_model);
    m_texture->bind();
    // Texture unit 0
    m_program.setUniformValue("texture", 0);


    // Draw cube geometry using indices from VBO 1
    f->glDrawElements(GL_TRIANGLES, m_sphere.getIndices().size(), GL_UNSIGNED_SHORT, 0);

    m_program.release();
}

void Dialog::nextFrame()
{
    // Removing this condition causes the model to shrink
    if (m_cameraVelocity.x() != 0.0f)
    {
        m_model.rotate(CAMERA_SPEED, 0.0f, m_cameraVelocity.x(), 0.0f);
    }
    if (m_cameraVelocity.y() != 0.0f)
    {
        QMatrix4x4 rot;
        rot.rotate(CAMERA_SPEED, -m_cameraVelocity.y(), 0.0f, 0.0f);
        m_model = rot * m_model;
    }

//    QVector3D axis(-m_cameraVelocity.y(), m_cameraVelocity.x(), 0.0f);
//    if (!axis.isNull())
//    {
//        QMatrix4x4 rot;
//        rot.rotate(CAMERA_SPEED, axis);
//        m_model = rot * m_model;
//    }

    //update the window (this will trigger paintEvent)
    update();
}

