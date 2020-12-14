#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "glwindowmanager.h"
#include "glshaderloader.h"
#include "gltypes.h"
#include <memory>

namespace LearnOGL
{
	class GLContext
	{
		public:
			GLContext();
			virtual ~GLContext();

		private:
			void loadGLAD();
			void setupGL();
			void loopGL();
			void handleInput();
			void destroyWindowManager();
			GLWindowSettings setupWindowSettings();
			gl_objid_t loadCompileShader(std::string shaderFile, gl_shader_t shaderType);

		private:
			std::unique_ptr<GLWindowManager> windowManager;
			GLShaderLoader shaderLoader;
	};
}

#endif // GLCONTEXT_H
