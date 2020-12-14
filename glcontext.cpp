#include "glcontext.h"
#include <iostream>

namespace LearnOGL
{
	GLContext::GLContext()
	{
		this->windowManager = std::make_unique<GLWindowManager>(setupWindowSettings());
		this->windowManager->displayWindow();

		try {
			loadGLAD();
			setupGL();

			while(this->windowManager->processWindow())
			{
				loopGL();
			}
		}

		catch (...) {
			this->windowManager->closeWindow();
			throw;
		}

		this->windowManager.reset();
	}

	void GLContext::loadGLAD()
	{
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to load GLFW GL addresses");
		}
	}

	void GLContext::setupGL()
	{
		glViewport(0, 0, 800, 600);

		loadCompileShader("vertexshader", GL_VERTEX_SHADER);
		loadCompileShader("fragshader", GL_FRAGMENT_SHADER);
	}

	void GLContext::loopGL()
	{
		handleInput();

		glClearColor(0.0f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		float glTriangleVertex[] = {
			-0.4f, 0.0f, 0.0f,
			0.1f, 0.3f, 0.0f,
			0.0f, -0.3f, 0.0f
		};

		gl_objid_t vertexBufferObjId;

		glGenBuffers(1, &vertexBufferObjId);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glTriangleVertex), glTriangleVertex, GL_STATIC_DRAW);
	}

	void GLContext::handleInput()
	{
		if (this->windowManager->readKeyboardKey(GLFW_KEY_ESCAPE) != GLFW_RELEASE)
		{
			this->windowManager->notifyWindowClose();
		}
	}

	static void onGLWindowResized(GLFWwindow *, int newWidth, int newHeight)
	{
		glViewport(0, 0, newWidth, newHeight);
	}

	GLWindowSettings GLContext::setupWindowSettings()
	{
		GLWindowSettings windowSettings;

		windowSettings.title = "Janela de teste GL";

		windowSettings.resizeCallback = onGLWindowResized;

		return windowSettings;
	}

	gl_objid_t GLContext::loadCompileShader(std::string shaderFile, gl_shader_t shaderType)
	{
		std::string vertexShader = this->shaderLoader.loadShader(shaderFile);
		const char* const vertexShaderData = vertexShader.c_str();

		gl_objid_t vertexShaderId = glCreateShader(shaderType);
		glShaderSource(vertexShaderId, 1, &vertexShaderData, nullptr);
		glCompileShader(vertexShaderId);

		int success;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShaderId, sizeof(infoLog), nullptr, infoLog);

			throw std::runtime_error("shader error: " + std::string(infoLog));
		}

		return vertexShaderId;
	}

	GLContext::~GLContext()
	{

	}
}

