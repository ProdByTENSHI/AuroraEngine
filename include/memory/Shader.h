#pragma once

#include <string>
#include <unordered_map>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "globals/AuroraTypes.hpp"

namespace Aurora
{
	constexpr unsigned int INVALID_SHADER = 0xFFFFF;

	class Shader
	{
	public:
		Shader();
		// Create a Shader from external Shader Source Files
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind();
		void Unbind();

		// Set Uniforms
		GLint GetUniformLocation(const std::string& name);
		GLint GetSsboIndex(const std::string& name);

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform3f(const std::string& name, const glm::vec3& vec);
		void SetUniform4f(const std::string& name, const glm::vec4& vec);
		void SetUniformMat4(const std::string& name, const glm::mat4& mat);

		inline GLuint GetProgram() { return m_Program; }

		bool operator==(const Shader& other) const noexcept
		{
			return m_Id == other.m_Id;
		}

		bool operator!=(const Shader& other) const noexcept
		{
			return m_Id != other.m_Id;
		}

	public:
		static u32 s_IdCount;

		// Internal Shader ID
		const u32 m_Id;

	private:
		// Create Shader from Vertex Shader Source and Fragment Shader Source
		void Create(const std::string& vertexSource, const std::string& fragmentSource);

		// Load a Shader Source File and return it's source code
		const std::string LoadShader(const std::string& path);

		GLuint CompileShader(GLuint type, const std::string& source);

		GLuint m_Program = 0;
		GLuint m_VertexShader = 0;
		GLuint m_FragmentShader = 0;

		std::unordered_map<std::string, GLint> m_UniformLocationCache;
		std::unordered_map<std::string, GLint> m_SsboLocationCache;
	};
}