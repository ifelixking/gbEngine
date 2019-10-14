#pragma once

// ������Ⱦ�̣߳�������Ϣ���� �������߳���

namespace gbEngine {

	class API EnvBasic
	{
	public:
		EnvBasic();
		~EnvBasic();

		// ��ʼ��
		// OpenGL: ��ʼ��������Ⱦ�����ģ���ʼ��glew
		bool Init();

		void Release();

		class Window* CreateRenderWindow(Point location, Size size, void * parentWindow);
		
		void DestroyRenderWindow(Window* window);

		void ExecEventLoop();

	private:
		static void eventHandle(class Window * window, const struct Event * event, void * param);

	private:
		// std::vector<Window*> m_windowList;
		class EventManager* m_eventManager;
		
	};


}