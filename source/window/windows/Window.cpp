#include "stdafx.h"
#include "Window.h"

extern HMODULE g_win32ModuleHandle;
static const char* WNDCLASSNAME = "gbEngine_window";

namespace gbEngine {

	Window::Window()
		: m_hwnd(NULL), m_hdc(NULL), m_hrc(NULL), m_eventHandle(nullptr) {
	}

	Window::~Window() {
		assert(m_hwnd == NULL && m_hdc == NULL && m_hrc == NULL);
	}

	void Window::Create(Point location, Size size, void* parentWindow, EventHandle eventHandle) {
		assert(m_hwnd == NULL);
		WNDCLASSEX wndClass;
		auto bResult = GetClassInfoEx(g_win32ModuleHandle, WNDCLASSNAME, &wndClass);
		if (!bResult) {
			// 不存在这个窗口类，就创建它
			settingWNDCLASS(wndClass);
			auto result = RegisterClassEx(&wndClass); assert(result);
		}
		const char* title = "gbEngine";
		auto hwnd = CreateWindow(WNDCLASSNAME, title, WS_OVERLAPPEDWINDOW, location.X, location.Y, size.X, size.Y,
			(HWND)parentWindow, NULL, g_win32ModuleHandle, NULL); assert(hwnd);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);



		m_hwnd = hwnd;
		m_eventHandle = eventHandle;
	}

	void Window::settingWNDCLASS(WNDCLASSEX& wcex) {
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

	LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message)
		{
		case WM_SIZE: {
			Window* _this = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			POINTS pt = MAKEPOINTS(lParam);
			Event event = Event::Create(ET_SIZE);  event.size = Point(pt.x, pt.y);
			_this->m_eventHandle(_this, &event);
		}break;
		case WM_MOUSEWHEEL:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE: {
			//TestApp* _this = (TestApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			//_this->m_execParams.funcEvent(message, wParam, lParam);
		}break;
		case WM_DESTROY: PostQuitMessage(0); break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		return 0;
	}

	void Window::Destroy() {

	}

	void Window::Show(bool visible) {
		auto result = ShowWindow(m_hwnd, visible ? SW_SHOWNORMAL : SW_HIDE);
		assert(result);
	}

}