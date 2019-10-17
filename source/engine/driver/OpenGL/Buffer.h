#pragma once

NAMESPACE_BEGIN

class Buffer {
public:
	Buffer(unsigned int size, void * data);
	~Buffer();

	GLuint GetHandle() const { return m_handle; }

private:
	GLuint m_handle;

};

NAMESPACE_END