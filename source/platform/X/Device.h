#pragma once


NAMESPACE_BEGIN

struct Device {
	Display *display;
	::Window windowRoot;
	int defaultScreen;
	GLXFBConfig *fbConfig;
	XVisualInfo *visualInfo;
	Colormap colormap;
};

extern Device g_device;

NAMESPACE_END
