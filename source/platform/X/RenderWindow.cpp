#include "stdafx.h"
#include "RenderWindow.h"
#include "Device.h"
#include "EventManager.h"

NAMESPACE_BEGIN


const auto EVENT_MASK = ExposureMask | KeyPressMask | StructureNotifyMask;

static void openDevice(Device & device){
	auto displayName = getenv("DISPLAY"); assert(displayName);
	device.display = XOpenDisplay(displayName); assert(device.display);
	device.defaultScreen = DefaultScreen(device.display);
	int nelements, att[] = {GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_DOUBLEBUFFER, True, GLX_DEPTH_SIZE, 16, None};
	device.fbConfig = glXChooseFBConfig(device.display, device.defaultScreen, att, &nelements); assert(device.fbConfig);
	device.visualInfo = glXGetVisualFromFBConfig(device.display, *device.fbConfig); assert(device.visualInfo);
	device.windowRoot = RootWindow(device.display, device.defaultScreen);
	device.colormap = XCreateColormap(device.display, device.windowRoot, device.visualInfo->visual, AllocNone);
}

static void closeDevice(Device & device){
	XFreeColormap(device.display, device.colormap);
	XFree(device.fbConfig);
	XFree(device.visualInfo);
	XCloseDisplay(device.display);
	device.display = nullptr;
}

void RenderWindow::Initilize(){
	assert(g_device.display == nullptr);
	openDevice(g_device);
}

void RenderWindow::Release(){
	assert(g_device.display != nullptr);
	closeDevice(g_device);
}

RenderWindow::RenderWindow():m_eventManager(nullptr), m_xWindow(None){}

RenderWindow::~RenderWindow(){}

void RenderWindow::Create(Point location, Size size, void* parentWindow, class EventManager * eventManager){
	assert(g_device.display != nullptr);
	assert(m_xWindow == None);
    XSetWindowAttributes swa;
    swa.colormap = g_device.colormap;
    swa.event_mask = EVENT_MASK;
    unsigned long valueMask = CWColormap | CWEventMask;
    auto window = XCreateWindow(g_device.display, g_device.windowRoot, 100, 100, 640, 480, 0,
                                g_device.visualInfo->depth, InputOutput, g_device.visualInfo->visual,
                                valueMask, &swa);
	m_xWindow = window;
	m_eventManager = eventManager;
	eventManager->RegisterWindow(window, this);
}

void RenderWindow::Destroy(){
	assert(g_device.display != nullptr);
	assert(m_xWindow != None);
	XDestroyWindow(g_device.display, m_xWindow);
	m_eventManager->UnregisterWindow(m_xWindow);
}

void RenderWindow::Show(bool visible){
	assert(g_device.display != nullptr);
	assert(m_xWindow != None);
	XMapWindow(g_device.display, m_xWindow);
    XFlush(g_device.display);
}

NAMESPACE_END