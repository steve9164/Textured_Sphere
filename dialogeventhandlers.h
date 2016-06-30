#ifndef DIALOGEVENTHANDLERS_H
#define DIALOGEVENTHANDLERS_H

#include "eventhandler.h"
#include "dialog.h"

class Dialog::KeyEventPan : public EventHandler
{
public:
    KeyEventPan(Dialog& dialog);
    bool handleEvent(QEvent* event);

private:
    bool handleKeyEvent(QKeyEvent* event);

    Dialog& m_dialog;
};


class Dialog::MouseWheelEventZoom : public EventHandler
{
public:
    MouseWheelEventZoom(Dialog& renderer);
    bool handleEvent(QEvent* event);

private:
    bool handleMouseWheelEvent(QWheelEvent* event);

    Dialog& m_dialog;
};

class Dialog::KeyEventHandler : public EventHandler
{
public:
    KeyEventHandler(Dialog& dialog);
    bool handleEvent(QEvent* event);

private:
    bool handleKeyEvent(QKeyEvent* event);

    Dialog& m_dialog;
};


#endif // DIALOGEVENTHANDLERS_H
