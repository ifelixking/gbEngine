#pragma once

namespace gbEngine
{
	enum EventType {
		ET_INVALIDATE,
		ET_SIZE,
		ET_MOUSE,
		ET_KEYBOARD,
	};

	struct Event {
		EventType type;
		union {
			Point mouse;
			Point size;
		};

		static Event Create(EventType type) {
			char data[sizeof(Event)];
			Event* e = (Event*)data;
			e->type = type;
			return *e;
		}
	};



	typedef void (*EventHandle)(class Window* window, const struct Event* event);

}