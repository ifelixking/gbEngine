#include "stdafx.h"
#include "Device.h"
#include "RenderWindow.h"
#include "../../engine/driver/driver.h"

NAMESPACE_BEGIN

Device g_device;

Device::Device()
	: m_display(nullptr){
}

Device::~Device(){
	assert(m_display == nullptr);
}

void Device::Open(){
	assert(m_display == nullptr);
	auto displayName = getenv("DISPLAY"); assert(displayName);
	m_display = XOpenDisplay(displayName); assert(m_display);
	m_defaultScreen = DefaultScreen(m_display);
	int nelements, att[] = {GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_DOUBLEBUFFER, True, GLX_DEPTH_SIZE, 16, None};
	m_fbConfig = glXChooseFBConfig(m_display, m_defaultScreen, att, &nelements); assert(m_fbConfig);
	m_visualInfo = glXGetVisualFromFBConfig(m_display, *m_fbConfig); assert(m_visualInfo);
	m_windowRoot = RootWindow(m_display, m_defaultScreen);
	m_colormap = XCreateColormap(m_display, m_windowRoot, m_visualInfo->visual, AllocNone);

	// create a gl context for global resource shared
	m_glContext = glXCreateContext(m_display, m_visualInfo, nullptr, GL_TRUE); assert(m_glContext);

	this->BeginCreateResource();
	RenderDriverInit();
	this->EndCreateResource();
}

void Device::Close(){
	assert(m_display != nullptr);
	glXDestroyContext(m_display, m_glContext);
	XFreeColormap(m_display, m_colormap);
	XFree(m_fbConfig);
	XFree(m_visualInfo);
	XCloseDisplay(m_display);
	m_display = nullptr;
}

Window Device::CreateWindow(const Point & location, const Size & size) {
	assert(m_display != nullptr);
	XSetWindowAttributes swa;
	swa.colormap = m_colormap;
	swa.event_mask = EVENT_MASK;
	unsigned long valueMask = CWColormap | CWEventMask;
	auto window = XCreateWindow(m_display, m_windowRoot, location.X, location.Y, size.X, size.Y, 0,
								m_visualInfo->depth, InputOutput, m_visualInfo->visual,
								valueMask, &swa);
	return window;
}

void Device::DestroyWindow(Window window){
	assert(m_display != nullptr);
	XDestroyWindow(m_display, window);
}

GLXContext Device::CreateContext() {
	auto context = glXCreateContext(m_display, m_visualInfo, m_glContext, GL_TRUE); assert(context);
	return context;
}

void Device::DestroyContext(GLXContext context) {
	glXDestroyContext(m_display, context);
}

void Device::RenderBegin(RenderWindow * window){
	glXMakeCurrent(m_display, window->GetXWindow(), window->GetGLContext());
}

void Device::RenderEnd(RenderWindow * window){
	glXSwapBuffers(m_display, window->GetXWindow());
}

void Device::BeginCreateResource(){
	glXMakeCurrent(m_display, m_windowRoot, m_glContext);
}

void Device::EndCreateResource(){

}


NAMESPACE_END