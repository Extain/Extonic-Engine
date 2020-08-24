#ifndef LIGHT_SHADER_H
#define LIGHT_SHADER_H

#include "ShaderProgram.h"
#include "../graphics/Lights.h"
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
			lights.push_back(pointLight);
		}

		virtual void addLight(SpotLight spotLight, int pos)
		{
			if (spotLights.size() <= 1)
				spotLights.push_back(spotLight);
		}

		virtual void addLight(DirLight dirLight)
		{
			if (dirLights.size() <= 1)
				dirLights.push_back(dirLight);
		}

		virtual SpotLight getLight(int pos)
		{
			return spotLights[pos];
		}

		virtual void updateSpotLight(glm::vec3 pos, glm::vec3 direction, int index)
		{
			spotLights.at(index).position = pos;
			spotLights.at(index).direction = direction;
		}

		virtual ShaderProgram* getShader() { return program; }

		void use();

		virtual void unbind() { program->unbind(); }

	private:
		ShaderProgram* program;
		std::vector<PointLight> lights;
		std::vector<SpotLight> spotLights;
		std::vector<DirLight> dirLights;
	};
}
#endif
