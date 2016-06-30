#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QEvent>
#include <memory>

class EventHandler
{
public:
    class NoopEventHandler; // Empty event handler

    EventHandler(); // Must be defined in eventhandler.cpp because it needs full definition of NoopEventHandler
    EventHandler(std::shared_ptr<EventHandler> handler) : m_next(std::move(handler)) { }
    virtual ~EventHandler() { }
    virtual bool handleEvent(QEvent* event) = 0;
    virtual std::shared_ptr<EventHandler> chain(std::shared_ptr<EventHandler> handler)
    {
        if (handler)
            m_next = handler;
        return handler;
    }

protected:
    std::shared_ptr<EventHandler> m_next;
};

class EventHandler::NoopEventHandler : public EventHandler
{
public:
    NoopEventHandler() : EventHandler(nullptr) { } // Noop doesn't need an m_next because it is the end of the chain
    bool handleEvent(QEvent*) { return false; }
};

#endif // EVENTHANDLER_H
