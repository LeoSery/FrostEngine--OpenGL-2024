 #pragma once

#include "ECS/Component/IComponent.h"

#include "Render/VertexArrayObject.h"
#include "Render/Buffer.h"

#include "Core/Export.h"

#include "glm/vec4.hpp"

namespace frost::ECS
{
	class GameObject;
	class Transform;
	class Texture;
	enum class S_SpriteType
	{
		none,
		square,
		triangle,
		circle
	};

	class FROST_ENGINE_API SpriteRenderer : public IComponent
	{
		FROST_DEFINE_RTTI(SpriteRenderer)

	public:

		// Constructors and Destructors
		SpriteRenderer(GameObject& _GameObject);
		~SpriteRenderer();

		// Frost engine life cycle methods
		virtual void Start() override;
		virtual void Update(float _DeltaTime) override;
		virtual void Destroy() override;

		// Getters and Setters
		[[nodiscard]] virtual void GetData(bool _ForceLoggerDraw) const;

		[[nodiscard]] std::string GetTexture() const;
		[[nodiscard]] void SetTexture(const std::string& _NewTexturePath);

		[[nodiscard]] glm::vec4 GetColor() const;
		void SetColor(const glm::vec4& _NewColor);
		glm::vec4 m_color = { 1, 1, 1, 1 };
	private:
		std::string m_spriteTexturePath = "";

		frost::core::Texture* m_spriteTexture;


		float* vertices;
		unsigned int* indices;

	public:

		frost::core::Buffer VBO;
		frost::core::Buffer IBO;
		frost::core::VertexArrayObject VAO;
	};
}
