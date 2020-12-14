#ifndef GLSHADERLOADER_H
#define GLSHADERLOADER_H

#include <string>
#include <fstream>
#include <unordered_map>

namespace LearnOGL
{
	class GLShaderLoader
	{
		public:
			GLShaderLoader();

			std::string loadShader(std::string shaderFile, bool cache = true);
			void cacheShader(std::string shaderFile);
			std::optional<std::string> findCached(std::string shaderFile);

		private:
			std::string loadShaderFromFile(std::string shaderFile);

		private:
			std::unordered_map<std::string, std::string> shaderCache;
	};
}

#endif // GLSHADERLOADER_H
