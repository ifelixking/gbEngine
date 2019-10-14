#include "stdafx.h"
#include "EnvBasic.h"
#include "Window.h"
#include "EventManager.h"

namespace gbEngine {
	EnvBasic::EnvBasic()
		: m_eventManager(nullptr) {
	}

	EnvBasic::~EnvBasic() {

	}

	bool EnvBasic::Init() {
		m_eventManager = new EventManager(EnvBasic::eventHandle, this);
		return true;
	}

	void EnvBasic::Release() {
		delete m_eventManager; m_eventManager = nullptr;
	}

	class Window* EnvBasic::CreateRenderWindow(Point location, Size size, void* parentWindow) {
		Window* win = new Window;
		win->Create(location, size, parentWindow, this->m_eventManager);
		win->Show();
		// m_windowList.push_back(win);
		return win;
	}

	void EnvBasic::DestroyRenderWindow(Window* window) {
		// auto itorFind = std::find(m_windowList.begin(), m_windowList.end(), window);
		// if (itorFind == m_windowList.end()) { assert(false); return; }
		// m_windowList.erase(itorFind);
		window->Destroy();
		delete window;
	}

	void EnvBasic::ExecEventLoop() {
		m_eventManager->ExecEventLoop();
	}

	void EnvBasic::eventHandle(class Window* window, const struct Event* event, void* param) {
		auto _this = (EnvBasic*)param;
		// TODO: 决定是否处理WM_PAINT
		// TODO: 路由给Surface， 有Surface下的ToolManager处理
	}
}