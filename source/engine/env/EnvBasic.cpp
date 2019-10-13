#include "stdafx.h"
#include "EnvBasic.h"

#ifdef _WIN32
#include "../window/windows/Window.h"
#endif

namespace gbEngine {
	EnvBasic::EnvBasic() {}

	EnvBasic::~EnvBasic() {}

	bool EnvBasic::Init() {
		return true;
	}

	void EnvBasic::Release() {}

	class Window* EnvBasic::CreateRenderWindow(Point location, Size size, void* parentWindow) {
		Window* win = new Window;
		win->Create(location, size, parentWindow, nullptr);
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
		
	}
}