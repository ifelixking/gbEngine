#pragma once

#include "../defines.h"

namespace gbEngine
{
	class Window
	{
	public:
		Window();
		~Window();

		void Create(Point location, Size size, void* parentWindow, EventHandle eventHandle);
		void Destroy();
		void Show(bool visible = true);

	private:
		static void settingWNDCLASS(WNDCLASSEX& wcex);
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_hwnd;
		HDC m_hdc;
		HGLRC m_hrc;
		EventHandle m_eventHandle;
	};


}