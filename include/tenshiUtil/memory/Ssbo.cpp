#include "Ssbo.h"

#include "debug/Logger.hpp"

namespace Aurora
{
	Ssbo::~Ssbo()
	{
		glDeleteBuffers(1, &m_Buffer);
	}

	void Ssbo::Create(GLsizei size, const std::string& name)
	{
		m_Name = name;

		glCreateBuffers(1, &m_Buffer);
		glNamedBufferStorage(m_Buffer, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
	}

	GLuint Ssbo::GetBufferBindingPoint(Aurora::Shader& shader)
	{
		return shader.GetSsboIndex(m_Name);
	}

	void Ssbo::BindToShader(Aurora::Shader& shader, u8 index)
	{
		GLuint _bindingPoint = GetBufferBindingPoint(shader);
		if (_bindingPoint == GL_INVALID_INDEX)
			return;

		glShaderStorageBlockBinding(shader.GetProgram(), _bindingPoint, index);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, m_Buffer);
	}

	void Ssbo::SubBufferData(GLintptr offset, GLsizei size, const void* data)
	{
		glNamedBufferSubData(m_Buffer, offset, size, data);
	}
}