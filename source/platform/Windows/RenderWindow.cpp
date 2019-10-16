#include "stdafx.h"
#include "RenderWindow.h"
#include "EventManager.h"

extern HMODULE g_win32ModuleHandle;
static const char* WNDCLASSNAME = "gbEngine_window";

namespace gbEngine {

	RenderWindow::RenderWindow()
		: m_hwnd(NULL), m_hdc(NULL), m_hrc(NULL), m_eventManager(nullptr) {
	}

	RenderWindow::~RenderWindow() {
		assert(m_hwnd == NULL && m_hdc == NULL && m_hrc == NULL);
	}

	void RenderWindow::Create(Point location, Size size, void* parentWindow, EventManager* eventManager) {
		assert(m_hwnd == NULL);
		WNDCLASSEX wndClass;
		auto bResult = GetClassInfoEx(g_win32ModuleHandle, WNDCLASSNAME, &wndClass);
		if (!bResult) {
			settingWNDCLASS(wndClass);
			auto result = RegisterClassEx(&wndClass); assert(result);
		}
		const char* title = "gbEngine";
		auto hwnd = CreateWindow(WNDCLASSNAME, title, WS_OVERLAPPEDWINDOW, location.X, location.Y, size.X, size.Y,
			(HWND)parentWindow, NULL, g_win32ModuleHandle, NULL); assert(hwnd);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);

		m_hwnd = hwnd;
		m_eventManager = eventManager;
	}

	void RenderWindow::settingWNDCLASS(WNDCLASSEX& wcex) {
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = g_win32ModuleHandle;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = WNDCLASSNAME;
		wcex.hIconSm = NULL;
	}

	LRESULT CALLBACK RenderWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		MouseAction mouseAction; int delta = 0;
		switch (message)
		{
		case WM_SIZE: {
			RenderWindow* _this = (RenderWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			POINTS pt = MAKEPOINTS(lParam);
			Event event = Event::Create(EventType::ET_SIZE);  event.sizeEvent.size = Point(pt.x, pt.y);
			_this->m_eventManager->ProcessWindowEvent(_this, &event);
		}break;
		case WM_MOUSEWHEEL:
			delta = GET_WHEEL_DELTA_WPARAM(wParam);
			mouseAction = MouseAction::MA_WHEEL;			
			goto L_MOUSE_CASE;
		case WM_LBUTTONDOWN:
			mouseAction = MouseAction::MA_LBUTTONDOWN;
			goto L_MOUSE_CASE;
		case WM_RBUTTONDOWN:
			mouseAction = MouseAction::MA_RBUTTONDOWN;
			goto L_MOUSE_CASE;
		case WM_MBUTTONDOWN:
			mouseAction = MouseAction::MA_MBUTTONDOWN;
			goto L_MOUSE_CASE;
		case WM_LBUTTONUP:
			mouseAction = MouseAction::MA_LBUTTONUP;
			goto L_MOUSE_CASE;
		case WM_RBUTTONUP:
			mouseAction = MouseAction::MA_RBUTTONUP;
			goto L_MOUSE_CASE;
		case WM_MBUTTONUP:
			mouseAction = MouseAction::MA_MBUTTONUP;
			goto L_MOUSE_CASE;
		case WM_MOUSEMOVE: {
			mouseAction = MouseAction::MA_MOVE;
			L_MOUSE_CASE:
			RenderWindow* _this = (RenderWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			POINTS pt = MAKEPOINTS(lParam);
			Event event = Event::Create(EventType::ET_MOUSE);
			event.mouseEvent.action = mouseAction;
			event.mouseEvent.position = Point(pt.x, pt.y);
			event.mouseEvent.delta = delta;
			_this->m_eventManager->ProcessWindowEvent(_this, &event);
		}break;
		case WM_DESTROY: PostQuitMessage(0); break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		return 0;
	}

	void RenderWindow::Destroy() {

	}

	void RenderWindow::Show(bool visible) {
		ShowWindow(m_hwnd, visible ? SW_SHOWNORMAL : SW_HIDE);
	}

}