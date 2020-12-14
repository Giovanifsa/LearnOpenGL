#include "glwindowmanager.h"
#include <stdexcept>

namespace LearnOGL
{
	static void checkIfWindowActive(GLFWwindow *windowPtr)
	{
		if (!windowPtr) {
			throw std::runtime_error("No window is active");
		}
	}

	GLWindowManager::GLWindowManager(GLWindowSettings windowSettings) : windowSettings(windowSettings)
	{

	}

	GLWindowManager::~GLWindowManager()
	{
		if (this->window)
		{
			this->closeWindow();
		}
	}

	void GLWindowManager::displayWindow()
	{
		if (this->window)
		{
			throw std::runtime_error("Window is already active.");
		}

		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->window = glfwCreateWindow(800, 600, this->windowSettings.title.c_str(), nullptr, nullptr);

		if (!this->window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to initialize GLFW window");
		}

		glfwMakeContextCurrent(this->window);

		glfwSetFramebufferSizeCallback(this->window, this->windowSettings.resizeCallback);
	}

	void GLWindowManager::closeWindow()
	{
		checkIfWindowActive(this->window);

		glfwDestroyWindow(this->window);

		glfwTerminate();

		this->window = nullptr;
	}

	bool GLWindowManager::processWindow()
	{
		checkIfWindowActive(this->window);

		glfwSwapBuffers(this->window);

		glfwPollEvents();

		if (glfwWindowShouldClose(this->window))
		{
			//Once closed, this pointer may have been destroyed
			//Any subsequent calls to this must be avoided
			this->closeWindow();

			return false;
		}

		return true;
	}

	glfw_key_state GLWindowManager::readKeyboardKey(glfw_key key)
	{
		return glfwGetKey(this->window, key);
	}

	void GLWindowManager::notifyWindowClose()
	{
		glfwSetWindowShouldClose(this->window, true);
	}
}
