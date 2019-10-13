#pragma once

// 所有渲染线程，窗口消息处理 都在主线程中

namespace gbEngine {

	class API EnvBasic
	{
	public:
		EnvBasic();
		~EnvBasic();

		// 初始化
		// OpenGL: 初始化主的渲染上下文，初始化glew
		bool Init();

		void Release();

		class Window* CreateRenderWindow(Point location, Size size, void * parentWindow);
		
		void DestroyRenderWindow(Window* window);

		void ExecEventLoop();

	private:
		// std::vector<Window*> m_windowList;
	};


}