#include "stdafx.h"
#include "EnvBasic.h"
#include "Device.h"
#include "RenderWindow.h"
#include "EventManager.h"
#include "../../engine/core/Surface.h"

namespace gbEngine {
	EnvBasic::EnvBasic()
		: m_eventManager(nullptr) {
	}

	EnvBasic::~EnvBasic() {

	}

	bool EnvBasic::Init() {
		g_device.Open();
		m_eventManager = new EventManager(EnvBasic::eventHandle, this);
		return true;
	}

	void EnvBasic::Release() {
		delete m_eventManager; m_eventManager = nullptr;
		g_device.Close();
	}

	void EnvBasic::BeginCreateResource(){
		g_device.BeginCreateResource();
	}
	void EnvBasic::EndCreateResource(){
		g_device.EndCreateResource();
	}

	class RenderWindow* EnvBasic::CreateRenderWindow(Point location, Size size, void* parentWindow) {
		RenderWindow* win = new RenderWindow;
		win->Create(location, size, parentWindow, this->m_eventManager);
		win->Show();
		// m_windowList.push_back(win);
		return win;
	}

	void EnvBasic::DestroyRenderWindow(RenderWindow* window) {
		// auto itorFind = std::find(m_windowList.begin(), m_windowList.end(), window);
		// if (itorFind == m_windowList.end()) { assert(false); return; }
		// m_windowList.erase(itorFind);
		window->Destroy();
		delete window;
	}

	void EnvBasic::ExecEventLoop() {
		m_eventManager->ExecEventLoop();
	}

	void EnvBasic::eventHandle(class RenderWindow* window, const struct Event* event, void* param) {
		auto _this = (EnvBasic*)param;

		// WM_PAINT
		if (event->type == EventType::ET_INVALIDATE){
			g_device.RenderBegin(window);
			window->GetSurface()->Render();
			g_device.RenderEnd(window);
		}

		// TODO: Surface -> ToolManager
	}
}