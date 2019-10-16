#pragma once

NAMESPACE_BEGIN

class Buffer {
public:
	Buffer(unsigned int size, void * data);
	~Buffer();


private:
	GLuint m_handle;

};

NAMESPACE_END