#pragma once

#include "../defines.h"

NAMESPACE_BEGIN

class Window
{
public:
	Window();
	~Window();

	void Create(Point location, Size size, void* parentWindow, class EventManager * eventManager);
	void Destroy();
	void Show(bool visible = true);
};


NAMESPACE_END