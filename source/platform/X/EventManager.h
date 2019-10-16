#pragma once

#include "../defines.h"

namespace gbEngine {
	class EventManager {
	public:
		EventManager(EventHandle eventHandle, void * param);
		~EventManager();

		void ProcessWindowEvent(class RenderWindow * window, const struct Event *event);
		void ExecEventLoop();

		void RegisterWindow(::Window xWindow, class RenderWindow * window);
		void UnregisterWindow(::Window xWindow);

	private:
		EventHandle m_eventHandle;
		void * m_param;
		class EventManager_private * m_private;
	};
}


// gbEngine::EventManager::EventManager(void (*)(gbEngine::RenderWindow*, gbEngine::Event const*, void*), void*)