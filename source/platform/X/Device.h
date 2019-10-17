#pragma once


NAMESPACE_BEGIN

const auto EVENT_MASK = ExposureMask | KeyPressMask | StructureNotifyMask;

class Device {

public:
	Device();
	~Device();

	void Open();
	void Close();

	Display * GetDisplay() const { return m_display; }
	GLXContext GetGLContext() const { return m_glContext; }

	Window CreateWindow(const Point & location, const Size & size);
	void DestroyWindow(Window window);

	GLXContext CreateContext();
	void DestroyContext(GLXContext context);

	void RenderBegin(class RenderWindow * window);
	void RenderEnd(class RenderWindow * window);

	void BeginCreateResource();
	void EndCreateResource();

private:
	Display *m_display;
	Window m_windowRoot;
	int m_defaultScreen;
	GLXFBConfig *m_fbConfig;
	XVisualInfo *m_visualInfo;
	Colormap m_colormap;
	GLXContext m_glContext;
};

extern Device g_device;

NAMESPACE_END
