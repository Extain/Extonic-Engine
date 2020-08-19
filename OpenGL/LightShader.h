#ifndef LIGHT_SHADER_H
#define LIGHT_SHADER_H


#include "engine/Utils/Utility.h"
#include "engine/shaders/ShaderProgram.h"
#include "Lights.h"
#include <vector>

namespace Extonic {
	class LightShader
	{
	public:
		LightShader();

		void updateUniforms();

		virtual void addLight(PointLight pointLight, int pos) 
		{
			if (lights.size() <= 3)
				lights.push_back(pointLight);
		}

		virtual ShaderProgram getShader() { return *program; }

		void use();

		virtual void unbind() { program->unbind(); }

	private:
		ShaderProgram* program;
		std::vector<PointLight> lights;
	};
}
#endif
