#include "stdafx.h"
#include "EventManager.h"
#include "Device.h"

NAMESPACE_BEGIN

struct EventManager_private{

	typedef std::vector<std::pair<::Window, RenderWindow *>> RegWindowList;
	RegWindowList regWindowList;

	RegWindowList::iterator find(::Window xWindow){
		for(auto itor = regWindowList.begin(); itor!=regWindowList.end(); ++itor){
			if (itor->first == xWindow){
				return itor;
			}
		}
		return regWindowList.end();
	}
};

EventManager::EventManager(EventHandle eventHandle, void * param) 
	: m_private(new EventManager_private)
	, m_eventHandle(eventHandle)
	, m_param(param)
{}

EventManager::~EventManager() {

	delete m_private;
}

void EventManager::ProcessWindowEvent(class RenderWindow *window, const struct Event *event) {

}

void EventManager::ExecEventLoop() {
	XEvent xEvent;
	Event event = Event::Create();
	for (;;){
		XNextEvent(g_device.GetDisplay(), &xEvent);
		switch (xEvent.type) {
		case Expose:{
			event.type = EventType::ET_INVALIDATE;
		} break;
		case KeyPress:{
			auto keySys = XkbKeycodeToKeysym(g_device.GetDisplay(), xEvent.xkey.keycode, 0,
					(xEvent.xkey.state & ShiftMask) ? 1 : 0);
			event.type = EventType::ET_KEYBOARD; event.keyEvent.keyCode = keySys;
			if (keySys == XK_Escape) return;
		} break;
		default:
			continue;
		}
		auto itorFind = m_private->find(xEvent.xkey.window);
		if (itorFind == m_private->regWindowList.end()) { assert(false); continue; }
		auto window = itorFind->second;
		m_eventHandle(window, &event, m_param);
	}
}

void EventManager::RegisterWindow(::Window xWindow, class RenderWindow * window){
	m_private->regWindowList.emplace_back(std::make_pair(xWindow, window));
}


void EventManager::UnregisterWindow(::Window xWindow){
	auto itorFind = m_private->find(xWindow);
	if (itorFind == m_private->regWindowList.end()){ return; }
	m_private->regWindowList.erase(itorFind);
}

NAMESPACE_END