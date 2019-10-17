#include "stdafx.h"
#include "Shader.h"

NAMESPACE_BEGIN

Shader::Shader(SHADER_TYPE shaderType, const char *source)
		: m_shaderType(shaderType), m_source(source), m_handle(0) {

}

Shader::~Shader() {
	Clear();
}

bool Shader::Build(){
	Clear();
	if (m_source.empty()) { return false; }
	auto shader = glCreateShader(macro_convert_SHADER_TYPE(m_shaderType)); assert(shader);
	const char * sourceCode = m_source.c_str();
	glShaderSource(shader, 1, &sourceCode, nullptr);
	glCompileShader(shader);
	GLint status; glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		// compile failed
		GLint infoLen; glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen); assert(infoLen);
		m_buildOutput.resize(infoLen);
		glGetShaderInfoLog(shader, infoLen, nullptr, (GLchar *) m_buildOutput.c_str());
		glDeleteShader(shader);
		assert(false); return false;
	}
	m_handle = shader;
	return true;
}

void Shader::Clear(){
	m_buildOutput.clear();
	if (m_handle){
		glDeleteShader(m_handle);
		m_handle = 0;
	}
}

NAMESPACE_END