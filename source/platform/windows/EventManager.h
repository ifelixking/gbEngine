#pragma once

#include "../defines.h"

namespace gbEngine {

	class EventManager
	{
	public:
		EventManager(EventHandle eventHandle, void * param);
		~EventManager();

		void ProcessWindowEvent(class RenderWindow * window, const struct Event *event);
		void ExecEventLoop();

	private:
		EventHandle m_eventHandle;
		void* m_eventHandleParam;
	};


}