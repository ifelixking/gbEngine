//OpenGL-Version	GLSL-Version
//2.0				110
//2.1				120
//3.0				130
//3.1				140
//3.2				150
//3.3				330
//4.0				400
//4.1				410
//4.2				420
//4.3				430

//OpenGL-ES-Version	GLSL-ES-Version
//2.0				100
//3.0				300

#include "stdafx.h"
#include "../driver.h"

NAMESPACE_BEGIN

static std::string g_driverInfo;
const char * RenderDriverInfo(){
	return g_driverInfo.c_str();
}

void RenderDriverInit(){
	GLenum err = glewInit();
	assert(GLEW_OK == err);

	auto glewVer = (const char *)glewGetString(GLEW_VERSION);
	auto glVer = (const char *)glGetString(GL_VERSION);
	auto glslVer = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::stringstream tmp;
	tmp<<"OpenGL Version: "<<glVer<<" \nGLSL Version: "<<glslVer<<" \nGLEW Version: "<<glewVer<<" \n";
	g_driverInfo = tmp.str();

	// TODO: only for debug
	std::cout<<g_driverInfo<<std::endl;
}

unsigned int macro_convert_SHADER_TYPE(SHADER_TYPE shaderType){
	switch (shaderType){
		case SHADER_TYPE::ST_VERTEX: return GL_VERTEX_SHADER;
		case SHADER_TYPE::ST_FRAGMENT: return GL_FRAGMENT_SHADER;
		case SHADER_TYPE ::ST_GEOMETRY: return GL_GEOMETRY_SHADER;
		case SHADER_TYPE ::ST_COMPUTE: return GL_COMPUTE_SHADER;
	}
}

NAMESPACE_END