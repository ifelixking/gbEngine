#pragma once

NAMESPACE_BEGIN

class SimpleRect {

public:
	SimpleRect();
	~SimpleRect();

	void Init();
	void Release();
	void Render();

private:
	class Program * m_program;
	std::vector<GLuint> m_attrLocas;
	std::vector<GLuint> m_unifLocas;
};

extern SimpleRect g_simpleRect;

NAMESPACE_END