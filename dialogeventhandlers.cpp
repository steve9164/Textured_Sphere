#include "dialogeventhandlers.h"
#include "dialog.h"
#include <QKeyEvent>
#include <QDebug>

constexpr float CAMERA_ZOOM_FACTOR = 500.0f;

Dialog::KeyEventPan::KeyEventPan(Dialog& dialog)
    : m_dialog(dialog)
{ }

bool Dialog::KeyEventPan::handleEvent(QEvent* event)
{
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
    return (keyEvent && handleKeyEvent(keyEvent)) || m_next->handleEvent(event);
}

bool Dialog::KeyEventPan::handleKeyEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
    {
        return false;
    }
    else if (event->type() == QEvent::KeyPress)
    {
        switch (event->key())
        {
        case Qt::Key_W:
            m_dialog.m_cameraVelocity += QVector3D(0, 1, 0);
            return true;
        case Qt::Key_A:
            m_dialog.m_cameraVelocity += QVector3D(-1, 0, 0);
            return true;
        case Qt::Key_S:
            m_dialog.m_cameraVelocity += QVector3D(0, -1, 0);
            return true;
        case Qt::Key_D:
            m_dialog.m_cameraVelocity += QVector3D(1, 0, 0);
            return true;
        default:
            return false;
        }
    }
    else if (event->type() == QEvent::KeyRelease)
    {
        switch (event->key())
        {
        case Qt::Key_W:
            m_dialog.m_cameraVelocity -= QVector3D(0, 1, 0);
            return true;
        case Qt::Key_A:
            m_dialog.m_cameraVelocity -= QVector3D(-1, 0, 0);
            return true;
        case Qt::Key_S:
            m_dialog.m_cameraVelocity -= QVector3D(0, -1, 0);
            return true;
        case Qt::Key_D:
            m_dialog.m_cameraVelocity -= QVector3D(1, 0, 0);
            return true;
        default:
            return false;
        }
    }
    else
    {
        return false;
    }
}

Dialog::MouseWheelEventZoom::MouseWheelEventZoom(Dialog& dialog)
    : m_dialog(dialog)
{ }

bool Dialog::MouseWheelEventZoom::handleEvent(QEvent* event)
{
    QWheelEvent* mouseWheelEvent = dynamic_cast<QWheelEvent*>(event);
    return (mouseWheelEvent && handleMouseWheelEvent(mouseWheelEvent)) || m_next->handleEvent(event);
}

bool Dialog::MouseWheelEventZoom::handleMouseWheelEvent(QWheelEvent* event)
{
    if (!event->angleDelta().isNull())
    {
        QMatrix4x4 tr;
        tr.translate(0, 0, (event->angleDelta().y() / CAMERA_ZOOM_FACTOR));
        m_dialog.m_view = tr * m_dialog.m_view;
        return true;
    }
    else
    {
        return false;
    }
}

Dialog::KeyEventHandler::KeyEventHandler(Dialog &dialog)
    : m_dialog(dialog)
{ }

bool Dialog::KeyEventHandler::handleEvent(QEvent *event)
{
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
    return (keyEvent && handleKeyEvent(keyEvent)) ||  m_next->handleEvent(event);
}

bool Dialog::KeyEventHandler::handleKeyEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        return false;
    }
    else if (event->type() == QEvent::KeyPress)
    {
        switch (event->key())
        {
        // Add keys to handle here
        case Qt::Key_Space:
        default:
            return false;
        }
    }
    else
    {
        return false;
    }
}
