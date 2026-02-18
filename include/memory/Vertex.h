#pragma once

#include <gl/glew.h>

#include "globals/AuroraTypes.hpp"

namespace Aurora
{
	struct Vertex
	{
		Vertex(GLfloat posX, GLfloat posY, GLfloat u, GLfloat v)
		{
			m_Position[0] = posX;
			m_Position[1] = posY;
			m_TexCoords[0] = u;
			m_TexCoords[1] = v;
		}

		GLfloat m_Position[2];
		GLfloat m_TexCoords[2];
	};
}