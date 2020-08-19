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
		~LightShader();

		void updateUniforms();

		virtual void addLight(PointLight pointLight, int pos) 
		{
			if (lights.size() <= 3)
				lights.push_back(pointLight);
		}

		/*virtual void addLight(SpotLight spotLight, int pos)
		{
			if (lights.size() <= 1)
				spotLights.push_back(spotLight);
		}*/

		virtual ShaderProgram getShader() { return *program; }

		void use();

		virtual void unbind() { program->unbind(); }

	private:
		ShaderProgram* program;
		std::vector<PointLight> lights;
		//std::vector<SpotLight> spotLights;
	};
}
#endif
