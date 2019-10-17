#pragma

#include "../driver.h"

NAMESPACE_BEGIN

class Shader {
public:
	Shader(SHADER_TYPE shaderType, const char * source);
	~Shader();

	SHADER_TYPE GetType() const { return m_shaderType; }
	void SetSource(const char * source) { m_source = source; }
	const char * GetSource() const { return m_source.c_str(); }
	bool Build();
	const char * GetBuildOutput() const { return m_buildOutput.c_str(); }
	void Clear();
	GLuint GetHandle() const { return m_handle; }

private:
	SHADER_TYPE m_shaderType;
	std::string m_source;
	std::string m_buildOutput;
	GLuint m_handle;
};

NAMESPACE_END