#pragma once

namespace gbEngine
{
	enum class EventType {
		ET_INVALIDATE,
		ET_SIZE,
		ET_MOUSE,
		ET_KEYBOARD,		
	};

	struct SizeEvent {
		Point size;
	};

	enum class MouseAction {
		MA_LBUTTONDOWN,
		MA_MBUTTONDOWN,
		MA_RBUTTONDOWN,
		MA_LBUTTONUP,
		MA_MBUTTONUP,
		MA_RBUTTONUP,
		MA_MOVE,
		MA_WHEEL,
	};

	enum MouseEventButtons : unsigned int {
		MEB_LEFT = 0x0001,
		MEB_RIGHT = 0x0002,
		MEB_MIDDLE = 0x0004,
		MEB_CONTROL = 0x0008,
		MEB_SHIFT = 0x0010,
		MEB_X1 = 0x0020,
		MEB_X2 = 0x0040,
	};

	struct MouseEvent {
		Point position;
		MouseAction action;
		MouseEventButtons buttons;
		int delta;
	};

	struct KeyEvent{
		int keyCode;
	};

	struct Event {
		EventType type;
		union {
			SizeEvent sizeEvent;
			MouseEvent mouseEvent;
			KeyEvent keyEvent;
		};

		static Event Create(EventType type) {
			char data[sizeof(Event)];
			Event* e = (Event*)data;
			e->type = type;
			return *e;
		}
	};



	typedef void (*EventHandle)(class RenderWindow* window, const struct Event* event, void * param);

}