#include "LightShader.h"

namespace Extonic {
	LightShader::LightShader() : program(new Extonic::ShaderProgram)
	{
		program->createShader(Extonic::Util::loadFileAsString("resources/shaders/lightVertex.glsl").c_str(), Extonic::Util::loadFileAsString("resources/shaders/lightFragment.glsl").c_str());
		std::cout << "Creating shaders!" << std::endl;
	}

	void LightShader::updateUniforms()
	{
		for (int i = 0; i < lights.size(); i++)
		{
			std::string pointLight = "pointLights[" + std::to_string(i) + "]";
			program->uniform3f(pointLight + ".position", lights[i].position);
			program->uniform3f(pointLight + ".ambient", lights[i].ambient.x, lights[i].ambient.y, lights[i].ambient.z);
			program->uniform3f(pointLight + ".diffuse", lights[i].diffuse.x, lights[i].diffuse.y, lights[i].diffuse.z);
			program->uniform3f(pointLight + ".specular", lights[i].specular.x, lights[i].specular.y, lights[i].specular.z);
			program->uniform1f(pointLight + ".constant", lights[i].constant);
			program->uniform1f(pointLight + ".linear", lights[i].linear);
			program->uniform1f(pointLight + ".quadratic", lights[i].quadratic);
		}

		/* for (int i = 0; i < spotLights.size(); i++)
		{
			program->uniform3f("spotLight.position", spotLights[i].position);
			program->uniform3f("spotLight.direction", spotLights[i].direction);
			program->uniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
			program->uniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			program->uniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
			program->uniform1f("spotLight.constant", 1.0f);
			program->uniform1f("spotLight.linear", 0.09);
			program->uniform1f("spotLight.quadratic", 0.032);
			program->uniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			program->uniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		} */
	}

	void LightShader::use() 
	{
		program->use();
	}

	LightShader::~LightShader()
	{
		delete program;
	}
}