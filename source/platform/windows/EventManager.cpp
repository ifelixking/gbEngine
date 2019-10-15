#include "stdafx.h"
#include "EventManager.h"
#include "../defines.h"

namespace gbEngine {

	EventManager::EventManager(EventHandle eventHandle, void * param)
		: m_eventHandle(eventHandle)
		, m_eventHandleParam(param){
	}
	EventManager::~EventManager() {}

	void EventManager::ProcessWindowEvent(class RenderWindow* window, const Event* event) {
		m_eventHandle(window, event, m_eventHandleParam);
	}

	void EventManager::ExecEventLoop() {
		MSG msg;
		for (;;) {
			if (GetMessage(&msg, NULL, NULL, NULL)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				break;
			}
		}
	}


}