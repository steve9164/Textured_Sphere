#include "eventhandler.h"

EventHandler::EventHandler(): m_next(new NoopEventHandler()) { }

