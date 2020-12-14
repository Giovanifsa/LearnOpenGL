#ifndef GLWINDOWSETTINGS_H
#define GLWINDOWSETTINGS_H

#include <string>
#include <functional>
#include "glheaders.h"

namespace LearnOGL
{
	struct GLWindowSettings
	{
		std::string title;
		GLFWframebuffersizefun resizeCallback;
	};
}

#endif // GLWINDOWSETTINGS_H
