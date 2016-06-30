#include "dialog.h"
#include "ui_dialog.h"
#include "dialogeventhandlers.h"

#include <array>

#include <QTimer>
#include <QOpenGLFunctions>
#include <QWidget>
#include <QQuaternion>
#include <QDebug>

#include <glm/glm.hpp>

constexpr float CAMERA_SPEED = 3.0f;

Dialog::Dialog(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::Dialog)
    , m_view()
    , m_cubeIndices(QOpenGLBuffer::IndexBuffer)
    , m_sphere(3,2)
    , m_eventHandler(new EventHandler::NoopEventHandler())
{

    //make the window appear
    ui->setupUi(this);
    this->resize(1200, 800);

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


static const char *vertexShaderSourceCore =
    "#version 120\n"
    "attribute vec4 vertex;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "void main() {\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 120\n"
    "void main() {\n"
    "   gl_FragColor = vec4(0, 1.0, 1.0, 1.0);\n"
    "}\n";

bool Dialog::event(QEvent* event)
{
    return m_eventHandler->handleEvent(event) || QOpenGLWidget::event(event);
}

void Dialog::initializeGL()
{

    m_view.setToIdentity();
    m_view.translate(0, 0, -10);

    glClearColor(0, 0, 0, 1);

    m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);

    m_program.link();

    m_program.bind();

    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);


    std::vector<glm::vec3> vertices = m_sphere.getVertices();
    std::vector<unsigned short> vertexIndices = m_sphere.getIndices();

    // Setup our vertex buffer object.
    m_cubeVertices.create();
    m_cubeVertices.bind();
    m_cubeVertices.allocate(vertices.data(), vertices.size() * sizeof(glm::vec3));

    m_cubeIndices.create();
    m_cubeIndices.bind();
    m_cubeIndices.allocate(vertexIndices.data(), vertexIndices.size() * sizeof(GLushort));

    // Tell OpenGL programmable pipeline how to locate vertex position data
    m_program.enableAttributeArray("vertex");
    m_program.setAttributeBuffer("vertex", GL_FLOAT, 0, 3, sizeof(glm::vec3));

    m_program.release();

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


    // Draw cube geometry using indices from VBO 1
    f->glDrawElements(GL_TRIANGLES, m_sphere.getIndices().size(), GL_UNSIGNED_SHORT, 0);

    m_program.release();
}

void Dialog::nextFrame()
{
    // Removing this condition causes the model to shrink
    QVector3D axis(-m_cameraVelocity.y(), m_cameraVelocity.x(), 0.0f);
    if (!axis.isNull())
    {
        QMatrix4x4 rot;
        rot.rotate(CAMERA_SPEED, axis);
        m_model = rot * m_model;
    }

    //update the window (this will trigger paintEvent)
    update();
}

