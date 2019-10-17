#pragma once

NAMESPACE_BEGIN

enum SHADER_TYPE {
	ST_VERTEX,
	ST_FRAGMENT,
	ST_GEOMETRY,
	ST_COMPUTE,
};

const char * RenderDriverInfo();

void RenderDriverInit();

unsigned int macro_convert_SHADER_TYPE(SHADER_TYPE shaderType);

NAMESPACE_END