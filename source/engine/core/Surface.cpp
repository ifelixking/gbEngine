#include "stdafx.h"
#include "Surface.h"

namespace gbEngine {
	Surface::Surface() {}
	
	Surface::~Surface() {}

	void Surface::Render() {
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}