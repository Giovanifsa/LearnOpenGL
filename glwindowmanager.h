#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "glheaders.h"
#include "glwindowsettings.h"
#include "gltypes.h"

namespace LearnOGL
{
	class GLWindowManager
	{
		public:
			GLWindowManager(GLWindowSettings windowSettings);
			GLWindowManager(const GLWindowManager&) = delete;
			virtual ~GLWindowManager();
			void displayWindow();
			bool processWindow();
			glfw_key_state readKeyboardKey(glfw_key key);
			void closeWindow();
			void notifyWindowClose();

		private:
			GLFWwindow* window = nullptr;
			GLWindowSettings windowSettings;
	};
}

#endif // GLWINDOW_H
