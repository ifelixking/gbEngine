#pragma once

//
namespace gbEngine {

	class API EnvBasic
	{
	public:
		EnvBasic();
		~EnvBasic();

		bool Init();
		void Release();

		void BeginCreateResource();
		void EndCreateResource();

		class RenderWindow* CreateRenderWindow(Point location, Size size, void * parentWindow);
		
		void DestroyRenderWindow(class RenderWindow* window);

		void ExecEventLoop();

	private:
		static void eventHandle(class RenderWindow * window, const struct Event * event, void * param);

	private:
		class EventManager* m_eventManager;
		
	};


}