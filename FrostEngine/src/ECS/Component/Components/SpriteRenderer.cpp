#include "ECS/Component/Components/SpriteRenderer.h"
#include "ECS/Entity/GameObject.h"
#include "Utils/Logger.h"

namespace frost::ECS
{
	SpriteRenderer::SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType) : IComponent(_GameObject)
	{
		SetSpriteType(_SpriteType);
	}

	SpriteRenderer::SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType, const glm::vec4& _NewColor) : IComponent(_GameObject)
	{
		SetSpriteType(_SpriteType);
		SetColor(_NewColor);
	}

	SpriteRenderer::SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType, const std::string& _SpriteTexturePath) : IComponent(_GameObject)
	{
		SetSpriteType(_SpriteType);
		SetTexture(_SpriteTexturePath);
	}

	SpriteRenderer::SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType, const std::string& _SpriteTexturePath, const glm::vec4& _Color) : IComponent(_GameObject)
	{
		SetSpriteType(_SpriteType);
		SetTexture(_SpriteTexturePath);
		SetColor(_Color);
	}

	SpriteRenderer::~SpriteRenderer()
	{

	}

	void SpriteRenderer::Start()
	{

	}

	void SpriteRenderer::Update(float /*fDeltaTime*/)
	{
		Transform* TransformC = GetParentObject().GetComponent<Transform>();
		TransformC;

		// Get instance of the renderer
		// Call the render method with the sprite type, texture, color and the transform
	}

	void SpriteRenderer::Destroy()
	{

	}

	void SpriteRenderer::GetData(bool _ShowImmediately) const
	{
		frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

		std::string TypeString = "{ Type: " + std::to_string(static_cast<int>(m_SpriteType)) + ";";
		std::string PathString = "{ Path: " + m_spriteTexturePath + ";";
		std::string ColorString = " Color: [r: " + std::to_string(m_color.r) + " g: " + std::to_string(m_color.g) + " b: " + std::to_string(m_color.b) + " a: " + std::to_string(m_color.a) + "]; }";

		Logger->LogInfo("- SpriteRenderer: " + TypeString + PathString + ColorString);

		if (_ShowImmediately)
			Logger->Show();
	}

	SpriteType SpriteRenderer::GetSpriteType() const
	{
		return m_SpriteType;
	}

	void SpriteRenderer::SetSpriteType(SpriteType _NewSpriteType)
	{
		m_SpriteType = _NewSpriteType;
	}

	std::string SpriteRenderer::GetTexture() const
	{
		return m_spriteTexturePath;
	}

	void SpriteRenderer::SetTexture(const std::string& _SpriteTexute)
	{
		m_spriteTexturePath = _SpriteTexute;
	}

	glm::vec4 SpriteRenderer::GetColor() const
	{
		return m_color;
	}

	void SpriteRenderer::SetColor(const glm::vec4& _Color)
	{
		m_color = _Color;
	}
}