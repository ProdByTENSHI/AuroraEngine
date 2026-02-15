#pragma once

#include <GL/glew.h>

#include "globals/AuroraTypes.hpp"
#include "memory/Shader.h"

namespace Aurora
{
	class Ssbo
	{
	public:
		~Ssbo();

		void Create(GLsizei size, const std::string& name);

		GLuint GetBufferBindingPoint(Aurora::Shader& shader);
		void BindToShader(Aurora::Shader& shader, u8 index);
		void SubBufferData(GLintptr offset, GLsizei size, const void* data);

	private:
		GLuint m_Buffer = 0;
		std::string m_Name;
	};
}