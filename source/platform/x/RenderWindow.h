#pragma once

#include "../defines.h"

NAMESPACE_BEGIN

class RenderWindow
{
public:
	RenderWindow();
	~RenderWindow();

	static void Initilize();
	static void Release();

	void Create(Point location, Size size, void* parentWindow, class EventManager * eventManager);
	void Destroy();
	void Show(bool visible = true);

private:
	Window m_xWindow;
	class EventManager * m_eventManager;
};


NAMESPACE_END