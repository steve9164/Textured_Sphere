#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include "sphere.h"

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
    void initializeGL();
    void paintGL();


private:
    Ui::Dialog* ui;
    QTimer* m_timer; //Timer object for triggering updates

    QMatrix4x4 m_view;
    QMatrix4x4 m_proj;

    QOpenGLShaderProgram m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_cubeVertices;
    QOpenGLBuffer m_cubeIndices;

    Sphere m_sphere;

};

#endif // DIALOG_H
