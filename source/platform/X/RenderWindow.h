#pragma once

#include "../defines.h"

NAMESPACE_BEGIN

class API RenderWindow
{
public:
	RenderWindow();
	~RenderWindow();

public: // internal
	static void Initialize();
	static void Release();

	void Create(Point location, Size size, void* parentWindow, class EventManager * eventManager);
	void Destroy();
	void Show(bool visible = true);

	Window GetXWindow() const { return m_xWindow; }
	GLXContext GetGLContext() const { return m_glContext; }

	class Surface * GetSurface() const { m_surface; }

private:
	class Surface * m_surface;
	Window m_xWindow;
	class EventManager * m_eventManager;
	GLXContext m_glContext;
};


NAMESPACE_END