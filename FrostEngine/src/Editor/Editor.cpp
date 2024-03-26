#include "Editor/Editor.h"


#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

#include "Core/Window.h"
#include "Utils/Logger.h"
#include "ECS/Component/Components/Transform.h"


#include "GLFW/glfw3.h"


namespace frost::editor 
{
    Editor* Editor::m_Instance = nullptr;


    Editor::Editor()
    {

    }

    Editor::~Editor()
    {

    }

    Editor* Editor::GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = new Editor();
        }

        return m_Instance;
    }

    int Editor::DrawEditor()
	{
        frost::core::Scene* m_CurrentScene;
        frost::core::SceneManager* m_SceneManager;
        m_SceneManager = &frost::core::SceneManager::GetInstance();
        m_CurrentScene = &m_SceneManager->GetActiveScene();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(300, 700));
        if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse))
        {
            if (ImGui::Button("Add Player"))
            {
                //GameObject::AddChild;
            }
            if (ImGui::Button("Supp Player"))
            {
                //GameObject::Destroy;
            }
            DrawHierachyValue(m_CurrentScene);
            ImGui::End();
        }



        ImGui::SetNextWindowSize(ImVec2(300, 705));
        if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
        {
            ImGui::End();
        }
      
        //ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse);
        

       ImGui::SetNextWindowSize(ImVec2(1000, 80));
        if (ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoCollapse))
        {
            if (ImGui::Button("Launch Game"))
            {

            }
            ImGui::Button("Stop");
            ImGui::End();
        }
#ifdef _DEBUG
        //ImGui::SetNextWindowSize(ImVec2(1600, 200));
        if (ImGui::BeginChild("Logger", ImVec2(500, 200), true))
        {
            if (ImGui::BeginTabBar("Tabs"))
            {
                if (ImGui::BeginTabItem("Console"))
                {
                    frost::utils::Logger::GetInstance()->DrawLogger();
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }

            //ImGui::Button("Clear");
            ImGui::EndChild();
        }
#endif
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return 0;

	}

    int Editor::Init(const frost::core::Window* _Window)
    {
  
        if (!glfwInit()) {
            return -1;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(_Window->GetInternal()), true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();

       


        return 0;
    }

    void Editor::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Editor::DrawHierachyValue(frost::core::Scene* m_CurrentScene)
    {
        for(auto* child : m_CurrentScene->GetRoot()->GetChildren())
        {
            ((void)child);
            if (ImGui::Button("player"))
            {
                DrawInsperctorValue(child);
            }  
        }
    }

    void Editor::DrawInsperctorValue(frost::ECS::GameObject* m_child)
    {

        if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
        {
            
            frost::ECS::Transform* tr = m_child->GetComponent<  frost::ECS::Transform>();
            // Get Transform //
            //ImGui::InputFloat2("Transform[X/Y]", &tr->position.x);
            if (ImGui::InputFloat2("Transform[X/Y]", &tr->position.x))
            {
               
            }
            // Get Rotation //
            //ImGui::InputFloat("Rotation", &tr->rotation);
            if (ImGui::InputFloat2("Rotation", &tr->rotation))
            {

            }
            // Get Scale //
            //ImGui::InputFloat2("Scale[X/Y]", &tr->scale.x);
            if (ImGui::InputFloat2("Scale[X / Y]", &tr->scale.x))
            {

            }

            //if (ImGui::Checkbox("IsCollide", &ISCollide))
            //{
            //    ISCollide = true;
            //    if (!ISCollide)
            //    {
            //        ISCollide = false;
            //    }
            //}
              
            //SpriteRenderer* sr = m_child->GetComponent<SpriteRenderer>();
            ImGui::End();
        }


    }
    
    void Editor::DeleteEditor()
    {
        if (m_Instance)
        {
            delete m_Instance;
            m_Instance = nullptr;
        }
    }

    
}