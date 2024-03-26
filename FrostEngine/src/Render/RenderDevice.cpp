#include "Render/RenderDevice.h"
#include "Core/Window.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/SignalSlot/Signal.h"
#include "Core/SignalSlot/Slot.h"

namespace frost::core
{
	RenderDevice* RenderDevice::m_instance = nullptr;

	struct RenderDevice::Internal
	{
		GLFWwindow* window = nullptr;
		std::vector<VertexArrayObject> VaoToRender;
	};

	RenderDevice::RenderDevice()
		:m_internal(new Internal)
	{}

	RenderDevice::~RenderDevice()
	{

		glDeleteVertexArrays(1, &m_vao);
		glfwTerminate();

	}

	RenderDevice* RenderDevice::Init(const Window* _window)
	{
		m_internal->window = reinterpret_cast<GLFWwindow*>(_window->GetInternal());
		glewInit();
	
		// set shaderProgram of used shader
		m_shaderProgram.InitShader("default.vert", "default.frag");
		m_shaderProgram.Enable();

		//for alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//PickUp Position of the shader in memory
		m_positionLocation	  =	glGetUniformLocation(m_shaderProgram.m_gl_ID, "uPosition");
		m_rotationLocation	  =	glGetUniformLocation(m_shaderProgram.m_gl_ID, "uRotation");
		m_scaleLocation		  =	glGetUniformLocation(m_shaderProgram.m_gl_ID, "uScale");
		m_aspectRatioLocation = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uAspectRatio");
		m_texture			  = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uTexture");
		m_zoom 				  = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uZoom");

		SetZoom(0.1f);
		SetClearColor(glm::vec4(0.0f,0.0f, 0.0f, 1.0f));

		return m_instance;
	}

	RenderDevice* RenderDevice::GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new RenderDevice();
		}

		return m_instance;
	}

	void RenderDevice::Update()
	{

		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		int w, h;
		glfwGetWindowSize(m_internal->window, &w, &h);
		glViewport(0, 0, w, h);
		glProgramUniform1f(m_shaderProgram.m_gl_ID, m_aspectRatioLocation, float(w) / float(h));

		for (int i = 0; i < GetVaoToRender().size(); i++)
		{
			GetVaoToRender()[i].Bind();
			//On Dit au shader les uniform du VAO
			glProgramUniform2f(m_shaderProgram.m_gl_ID, m_positionLocation, GetVaoToRender()[i].GetLocation().x, GetVaoToRender()[i].GetLocation().y);
			glProgramUniform1f(m_shaderProgram.m_gl_ID, m_rotationLocation, GetVaoToRender()[i].GetRotation());
			glProgramUniform2f(m_shaderProgram.m_gl_ID, m_scaleLocation, GetVaoToRender()[i].GetScale().x, GetVaoToRender()[i].GetScale().y);
			glProgramUniform1i(m_shaderProgram.m_gl_ID, m_texture, 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		ClearVaosToRender();

	}
	void RenderDevice::SetZoom(float _zoom)
	{
		glProgramUniform1f(m_shaderProgram.m_gl_ID, m_zoom, _zoom);
	}

	float RenderDevice::GetZoom()
	{
		float toReturn;
		glGetUniformfv(m_shaderProgram.m_gl_ID, m_zoom, &toReturn);
		return toReturn;
	}

	void RenderDevice::SetClearColor(glm::vec4 _color)
	{
		m_clearColor = _color;
	}

	glm::vec4 RenderDevice::GetClearColor()
	{
		return m_clearColor;
	}

	void RenderDevice::AddVAO(VertexArrayObject _newVao)
	{
		m_internal->VaoToRender.push_back(_newVao);
	}

	void RenderDevice::ClearVaosToRender()
	{
		m_internal->VaoToRender.clear();
	}

	std::vector<VertexArrayObject> RenderDevice::GetVaoToRender()
	{
		return m_internal->VaoToRender;
	}
}

