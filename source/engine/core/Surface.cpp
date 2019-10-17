#include "stdafx.h"
#include "Surface.h"

#include "Device.h"
#include "SimpleRect.h"

namespace gbEngine {
	Surface::Surface() {
		g_device.BeginCreateResource();
		g_simpleRect.Init();
		g_device.EndCreateResource();
	}
	
	Surface::~Surface() {
		g_device.BeginCreateResource();
		g_simpleRect.Release();
		g_device.EndCreateResource();
	}

	void Surface::Render() {
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_simpleRect.Render();
	}
}