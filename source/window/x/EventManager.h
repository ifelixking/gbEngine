#pragma once

#include "../defines.h"

namespace gbEngine {
	class EventManager {
	public:
		EventManager(EventHandle eventHandle, void * param);
		~EventManager();

		void ProcessWindowEvent(class Window * window, const struct Event *event);
		void ExecEventLoop();
	};
}