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
	};


}