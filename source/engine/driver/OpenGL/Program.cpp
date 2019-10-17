#include "stdafx.h"
#include "Program.h"
#include "Shader.h"

NAMESPACE_BEGIN

Program::Program() : m_handle(0) {

}

Program::~Program(){
	Clean();
}

bool Program::Build(const char *vertexSource, const char *fragmentSource,
					const std::vector<std::string> &attribLocationNames, std::vector<GLuint> &attribLocations,
					const std::vector<std::string> &uniformLocationNames, std::vector<GLuint> &uniformLocations) {
	Clean();
	Shader vertexShader(ST_VERTEX, vertexSource), fragmentShader(ST_FRAGMENT, fragmentSource);
	if (!vertexShader.Build()) { m_buildOutput = vertexShader.GetBuildOutput(); return false; }
	if (!fragmentShader.Build()) { m_buildOutput = fragmentShader.GetBuildOutput(); return false; }

	m_handle = glCreateProgram(); assert(m_handle);
	glAttachShader(m_handle, vertexShader.GetHandle());
	glAttachShader(m_handle, fragmentShader.GetHandle());
	glLinkProgram(m_handle);
	GLint linkStatus; glGetProgramiv(m_handle, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus) {
		GLint infoLen; glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &infoLen); assert(infoLen);
		m_buildOutput.reserve(infoLen);
		glGetProgramInfoLog(m_handle, infoLen, nullptr, (GLchar *) m_buildOutput.c_str());
		glDeleteProgram(m_handle);
		m_handle = 0;
		assert(false); return false;
	}

	attribLocations.clear(); attribLocations.reserve(attribLocationNames.size());
	for (const std::string &name : attribLocationNames) {
		auto loc = glGetAttribLocation(m_handle, name.c_str()); assert(loc >= 0);
		attribLocations.push_back(loc);
	}

	uniformLocations.clear();
	uniformLocations.reserve(uniformLocationNames.size());
	for (const std::string &name : uniformLocationNames) {
		auto loc = glGetUniformLocation(m_handle, name.c_str()); assert(loc >= 0);
		uniformLocations.push_back(loc);
	}

	return true;
}

void Program::Use(const std::vector<const Attribute *> *attribData, const std::vector<const Uniform *> *uniformData) {
	glUseProgram(m_handle);
	for (auto item : *attribData) {
		glVertexAttribPointer(item->location, item->componentCountPerItem, item->componentDataType, GL_FALSE,
							  item->stride, item->pointer);
		glEnableVertexAttribArray(item->location);
	}
}

void Program::Clean() {
	m_buildOutput.clear();
	if (!m_handle) return;
	// 强制从当前上下文卸载, 否则只是标记删除(等待状态机没有使用时才删除)
	GLint currentProgram; glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	if (currentProgram == m_handle) { glUseProgram(0); }
	glDeleteProgram(m_handle);
	m_handle = 0;
}



NAMESPACE_END