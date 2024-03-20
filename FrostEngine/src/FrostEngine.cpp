#include "FrostEngine.h"
#include <Core/Input/Input.h>

namespace FrostEngine
{
	void Application::Init(const InitData& data)
	{
		m_Window = new frost::core::Window({ data.title.c_str(), data.size });
		frost::core::Input::GetInstance()->init(m_Window);
		m_RenderDevice = new frost::core::RenderDevice(*m_Window);
		m_SceneManager = &frost::core::SceneManager::GetInstance();
		m_CurrentScene = &m_SceneManager->GetActiveScene();
	}

	void Application::Run()
	{
		std::chrono::steady_clock::time_point lastUpdateTime = std::chrono::steady_clock::now();

		do
		{
			// Calculate delta time
			auto  now = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(now - lastUpdateTime).count();
			lastUpdateTime = now;

			Update(deltaTime);

			if (m_CurrentScene != nullptr)
			{
				UpdateObjectComponents(m_CurrentScene->GetRoot(), deltaTime);

				for (auto* child : m_CurrentScene->GetRoot()->GetChildren())
				{
					BrowseAllChilds(child, deltaTime);
				}
			}

			frost::core::Input::GetInstance()->Update();

			// temporary render update (replace with SpriteRenderer Update function)
			/////////////////////////////////////////////////////////////
			m_RenderDevice->Update();
			/////////////////////////////////////////////////////////////

			frost::utils::Logger::GetInstance()->Show();
		} while (m_Window->PollEvents());
	}

	void Application::Shutdown()
	{
		delete m_RenderDevice;
		delete m_Window;
	}

	void Application::BrowseAllChilds(frost::ECS::GameObject* _GameObject, float _DeltaTime)
	{
		if (!_GameObject)
			return;

		UpdateObjectComponents(_GameObject, _DeltaTime);

		for (auto* child : _GameObject->GetChildren())
		{
			if (child->IsActive())
				BrowseAllChilds(child, _DeltaTime);
		}
	}

	void Application::UpdateObjectComponents(frost::ECS::GameObject* _GameObject, float _DeltaTime)
	{
		for (auto* component : _GameObject->GetAllComponents())
		{
			if (component->IsActive())
				component->Update(_DeltaTime);
		}
	}
}