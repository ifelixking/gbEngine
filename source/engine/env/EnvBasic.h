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
		// std::vector<Window*> m_windowList;
	};


}