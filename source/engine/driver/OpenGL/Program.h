#pragma once

NAMESPACE_BEGIN

class Program {
public:
	Program();

	~Program();

	bool Build(const char *vertexSource, const char *fragmentSource,
			   const std::vector<std::string> &attribLocationNames, std::vector<GLuint> &attribLocations,
			   const std::vector<std::string> &uniformLocationNames, std::vector<GLuint> &uniformLocations);

	struct Attribute {
		GLuint location;				//
		GLint componentCountPerItem;	// 属性数组中每项的数据组成
		GLint componentDataType;		// 项的数据类型
		GLsizei stride;					// 每项间隔字节
		const void *pointer;			// CPU buffer 或 VBO 的数据偏移
		class Buffer * buffer;			// VBO
	};
	struct Uniform {
	};

	void Use(const std::vector<const Attribute *> * attribData, const std::vector<const Uniform *> * uniformData);

	void Clean();

private:
	std::string m_buildOutput;
	GLuint m_handle;
};

NAMESPACE_END