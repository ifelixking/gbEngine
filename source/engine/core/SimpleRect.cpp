#include "stdafx.h"
#include "SimpleRect.h"
#include "Program.h"

NAMESPACE_BEGIN

SimpleRect g_simpleRect;

SimpleRect::SimpleRect() : m_program(nullptr) {}

SimpleRect::~SimpleRect() {}

void SimpleRect::Init() {
	assert(m_program == nullptr);
	m_program = new Program;
	const char *vs =
			"attribute vec4 a_position;"
			"void main() {"
			"  gl_Position = a_position;"
			"}";
	const char *fs =
			// TODO need determine glsl version
			// "precision mediump float;"
			"void main() {"
			"  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);"
			"}";
	std::vector<std::string> attrNames;
	attrNames.emplace_back("a_position");
	std::vector<std::string> unifNames;
	m_program->Build(vs, fs, attrNames, m_attrLocas, unifNames, m_unifLocas);
}

void SimpleRect::Release() {

}

void SimpleRect::Render() {

	const GLfloat gTriangleVertices[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
	std::vector<const Program::Attribute *> attrs;
	Program::Attribute attr = {m_attrLocas.front(), 2, GL_FLOAT, 2 * sizeof(float), gTriangleVertices, nullptr};
	attrs.push_back(&attr);

	m_program->Use(&attrs, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

NAMESPACE_END