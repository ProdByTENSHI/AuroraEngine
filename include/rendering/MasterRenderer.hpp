#pragma once

#include <memory>
#include <vector>

#include "ecs/ECS_Definitions.h"
#include "globals/AuroraTypes.hpp"
#include "memory/Shader.h"
#include "memory/Texture.h"
#include "memory/Vertex.h"
#include "tenshiUtil/memory/Ssbo.h"
#include "tenshiUtil/memory/UniformBuffer.h"

namespace Aurora {
	constexpr u8 MAX_LAYERS = 32;

	// Sort Priority Order
	constexpr u64 LAYER_SHIFT = 56;
	constexpr u64 DEPTH_SHIFT = 40;
	constexpr u64 SHADER_SHIFT = 24;
	constexpr u64 TEXTURE_SHIFT = 0;

	constexpr u32 ENTITY_IDS_SSBO_BINDING_POINT = 0;

	// VAO Data Layout
	const u32 VAO_POS_INDEX = 0;
	const u32 VAO_TEX_INDEX = 1;
	const u32 VAO_COLOR_INDEX = 2;

	inline static const Vertex QUAD_VERTICES[6] =
	{
		// First triangle
		Vertex(-0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 1.0f, 0.0f),
		Vertex(0.5f,  0.5f, 1.0f, 1.0f),

		// Second triangle
		Vertex(0.5f,  0.5f, 1.0f, 1.0f),
		Vertex(-0.5f,  0.5f, 0.0f, 1.0f),
		Vertex(-0.5f, -0.5f, 0.0f, 0.0f)
	};

	constexpr uint64_t BuildSortKey(
		u8  layer,
		u16 depth,
		u32 shaderID,
		u32 textureID)
	{
		return
			(u64(layer) << LAYER_SHIFT) |
			(u64(depth) << DEPTH_SHIFT) |
			(u64(shaderID) << SHADER_SHIFT) |
			(u64(textureID) << TEXTURE_SHIFT);
	}

	// Layer is the highest priority
	// Within layer, minimize shader changes
	// Within shader, minimize texture binds

	// Define Render Layers here for better visibility
	enum class RenderLayers {
		Default = 0,
		Background = 1,
		Entities = 2,
		Foreground = 3
	};

	struct RenderCommand {
	public:
		// Sort Key - We Sort the Render Commands at Flushing Stage by this Key
		u64 m_SortKey = 0;

		std::shared_ptr<Texture> m_Texture;
		std::shared_ptr<Shader> m_Shader;

		// MSB R: << 24
		//     G  << 16
		//     B  << 8
		// LSB A
		u32 m_Color = 0;

		f32 m_PosX = 0.0f;
		f32 m_PosY = 0.0f;
		f32 m_Width = 0.0f;
		f32 m_Height = 0.0f;

		// Rotations are stored as radians internally
		// Rotations are performed from the Pivot Point
		f32 m_Rotation = 0.0f;
		f32 m_PivotX = 0.0f;
		f32 m_PivotY = 0.0f;

		u8  m_Transparency = 0xFF;
		i8  m_Depth = 0;
		u8  m_Layer = (u8)RenderLayers::Default;
		u8  m_Padding = 0; // explicit padding

		// OP Overloads
		bool operator<(const RenderCommand& other) const noexcept
		{
			return m_SortKey < other.m_SortKey;
		}
	};

	// A Batch is a group of Entities to Render with the same
	// Layer, Depth, Shader and Texture
	struct RenderBatch {
		// Important Data for the Batch can be retrieved from Key
		u64 m_SortKey = 0;

		std::vector<RenderCommand> m_Commands;

		u32 m_ShaderId = 0;
		u32 m_Texture = 0;

		GLuint m_Vao = 0;
		GLuint m_Vbo = 0;
	};

	class MasterRenderer {
	public:
		MasterRenderer();

		void Render();

		void PushRenderCommand(RenderCommand command);

	private:
		// Sorts the Render Command Buffer by Layer and Texture
		void SortRenderCommandBuffer();

	public:
		Ssbo m_EntityIdsSsbo;

		std::shared_ptr<Shader> m_SpriteShader = nullptr;

	private:
		// Systems can push their Render Command to this Buffer
		// The Commands will be sorted and batched before rendering
		std::vector<RenderCommand> m_RenderCmdBuffer;

		std::vector<RenderBatch> m_Batches;

		// -- Vertex Data for Sprites and Spritesheets
		GLuint m_SpriteVao = 0;
		GLuint m_SpriteVbo = 0;
	};
}