#include "stdafx.h"
#include "Buffer.h"

NAMESPACE_BEGIN

Buffer::Buffer(unsigned int size, void * data){
	glGenBuffers(1, &m_handle);
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Buffer::~Buffer(){
	glDeleteBuffers(1, &m_handle);
}


NAMESPACE_END
