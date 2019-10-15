#include "stdafx.h"
#include "EventManager.h"

NAMESPACE_BEGIN

EventManager::EventManager(EventHandle eventHandle, void * param) {}
EventManager::~EventManager() {}

void EventManager::ProcessWindowEvent(class Window *window, const struct Event *event) {}
void EventManager::ExecEventLoop() {}

NAMESPACE_END