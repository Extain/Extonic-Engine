#include "../Utils/Utility.h"
#include "LightShader.h"

namespace Extonic {
	LightShader::LightShader() : program(new Extonic::ShaderProgram)
	{
		std::cout << "Creating shaders!" << std::endl;
		program->createShader(Extonic::Util::loadFileAsString("resources/shaders/lightVertex.glsl").c_str(), Extonic::Util::loadFileAsString("resources/shaders/lightFragment.glsl").c_str());
	}

	void LightShader::updateUniforms()
	{

		program->uniform1i("pointLightAmt", lights.size());

		for (int i = 0; i < lights.size(); i++)
		{
			std::string pointLight = "pointLights[" + std::to_string(i) + "]";
			program->uniform3f(pointLight + ".position", lights[i].position);
			program->uniform3f(pointLight + ".ambient", lights[i].ambient);
			program->uniform3f(pointLight + ".diffuse", lights[i].diffuse);
			program->uniform3f(pointLight + ".specular", lights[i].specular);
			program->uniform1f(pointLight + ".constant", lights[i].constant);
			program->uniform1f(pointLight + ".linear", lights[i].linear);
			program->uniform1f(pointLight + ".quadratic", lights[i].quadratic);
		}

		for (int i = 0; i < spotLights.size(); i++)
		{
			program->uniform3f("spotLight.position", spotLights[i].position);
			program->uniform3f("spotLight.direction", spotLights[i].direction);
			program->uniform3f("spotLight.ambient", spotLights[i].ambient);
			program->uniform3f("spotLight.diffuse", spotLights[i].diffuse);
			program->uniform3f("spotLight.specular", spotLights[i].specular);
			program->uniform1f("spotLight.constant", spotLights[i].constant);
			program->uniform1f("spotLight.linear", spotLights[i].linear);
			program->uniform1f("spotLight.quadratic", spotLights[i].quadratic);
			program->uniform1f("spotLight.cutOff", spotLights[i].cutOff);
			program->uniform1f("spotLight.outerCutOff", spotLights[i].outerCutOff);
		}

		for (int i = 0; i < dirLights.size(); i++)
		{
			program->uniform3f("dirLight.direction", dirLights[i].direction);
			program->uniform3f("dirLight.ambient", dirLights[i].ambient);
			program->uniform3f("dirLight.diffuse", dirLights[i].diffuse);
			program->uniform3f("dirLight.specular", dirLights[i].specular);
		}
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