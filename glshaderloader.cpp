#include "glshaderloader.h"
#include <sstream>
#include <iostream>

namespace LearnOGL
{
	GLShaderLoader::GLShaderLoader()
	{

	}

	std::string GLShaderLoader::loadShader(std::string shaderFile, bool cache)
	{
		std::optional<std::string> cached = findCached(shaderFile);

		if (!cached)
		{
			if (cache)
			{
				cacheShader(shaderFile);
				cached = findCached(shaderFile);
			}

			else
			{
				return loadShaderFromFile(shaderFile);
			}
		}

		return cached.value();
	}

	void GLShaderLoader::cacheShader(std::string shaderFile)
	{
		std::optional<std::string> cached = findCached(shaderFile);

		if (!cached)
		{
			std::cout << "Cached shader file " << shaderFile << std::endl;
			this->shaderCache[shaderFile] = loadShaderFromFile(shaderFile);
		}
	}

	std::optional<std::string> GLShaderLoader::findCached(std::string shaderFile)
	{
		auto iterator = this->shaderCache.find(shaderFile);

		if (iterator == this->shaderCache.end())
		{
			return std::nullopt;
		}

		return std::optional(iterator->second);
	}

	std::string GLShaderLoader::loadShaderFromFile(std::string shaderFile)
	{
		std::ifstream ifstream;
		ifstream.open("./shader/" + shaderFile + ".glsl");

		if (ifstream.is_open())
		{
			std::ostringstream outsstream;
			outsstream << ifstream.rdbuf();

			std::string shader = outsstream.str();

			std::cout << "Loaded shader file " << shaderFile << std::endl;
			std::cout << "Shader Content: " << std::endl << shader << std::endl;

			return shader;
		}

		throw std::runtime_error("Failed to load shader file " + shaderFile);
	}
}
