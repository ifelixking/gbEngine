#pragma once

#include "../defines.h"

namespace gbEngine
{
	class RenderWindow
	{
	public:
		RenderWindow();
		~RenderWindow();

		static void Initilize(){}
		static void Release(){}

		void Create(Point location, Size size, void* parentWindow, class EventManager * eventManager);
		void Destroy();
		void Show(bool visible = true);

	private:
		static void settingWNDCLASS(WNDCLASSEX& wcex);
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_hwnd;
		HDC m_hdc;
		HGLRC m_hrc;
		class EventManager * m_eventManager;
		class Surface* m_surface;
	};


}