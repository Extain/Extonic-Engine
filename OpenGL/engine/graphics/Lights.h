#ifndef LIGHTS_H
#define LIGHTS_H
#include <glm.hpp>

struct PointLight {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	glm::vec3 position;
	glm::vec3 direction;

	float cutOff;
	float outerCutOff;
	
	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
#endif