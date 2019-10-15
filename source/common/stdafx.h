#pragma once

// std && stl
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <thread>
#include <cassert>

// opengl
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

// window system
#ifdef _WIN32
	#include <GL/wglew.h>
	#include <windows.h>
#endif

// library export
#ifdef _WIN32
	#define API __declspec(dllexport)
#else
	#define API
#endif


// x
#ifdef linux
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <GL/glx.h>
#include <pthread.h>
#endif

#define NAMESPACE_BEGIN namespace gbEngine {
#define NAMESPACE_END }

// 
#include "../math/math.h"