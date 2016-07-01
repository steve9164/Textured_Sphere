#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include "texturedsphere.h"

class EventHandler;


namespace Ui {
class Dialog;
}

class Dialog : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    virtual ~Dialog();

private slots:
    void nextFrame();

private:
    //handle key presses
    bool event(QEvent *event);

    void initializeGL();
    void paintGL();


private:
    Ui::Dialog* ui;
    QTimer* m_timer; //Timer object for triggering updates

    QMatrix4x4 m_view;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_model;

    QOpenGLShaderProgram m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_cubeVertices;
    QOpenGLBuffer m_cubeIndices;

    TexturedSphere m_sphere;

    QOpenGLTexture* m_texture;

    QVector3D m_cameraVelocity;

    std::unique_ptr<EventHandler> m_eventHandler;

    class KeyEventHandler;
    class KeyEventPan;
    class MouseWheelEventZoom;
};

#endif // DIALOG_H
