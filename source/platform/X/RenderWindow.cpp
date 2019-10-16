#include "stdafx.h"
#include "RenderWindow.h"
#include "Device.h"
#include "EventManager.h"
#include "../../engine/core/Surface.h"

NAMESPACE_BEGIN

void RenderWindow::Initialize(){
	g_device.Open();
}

void RenderWindow::Release(){
	g_device.Close();
}

RenderWindow::RenderWindow()
	: m_eventManager(nullptr),
	m_xWindow(None),
	m_surface(new Surface){
}

RenderWindow::~RenderWindow(){
	assert(m_xWindow == None);
	delete m_surface;
}

void RenderWindow::Create(Point location, Size size, void* parentWindow, class EventManager * eventManager){
	assert(m_xWindow == None);
	m_xWindow = g_device.CreateWindow(location, size);
	m_eventManager = eventManager;
	m_glContext = g_device.CreateContext();
	eventManager->RegisterWindow(m_xWindow, this);
}

void RenderWindow::Destroy(){
	assert(m_xWindow != None);
	g_device.DestroyWindow(m_xWindow); m_xWindow = None;
	m_eventManager->UnregisterWindow(m_xWindow);
}

void RenderWindow::Show(bool visible){
	assert(g_device.GetDisplay() != nullptr);
	assert(m_xWindow != None);
	XMapWindow(g_device.GetDisplay(), m_xWindow);
    XFlush(g_device.GetDisplay());
}

NAMESPACE_END