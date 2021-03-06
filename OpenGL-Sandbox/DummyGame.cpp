#include "DummyGame.h"
#include <engine\Utils\Utility.h>


Extonic::PerspectiveCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Extonic::ShaderProgram lightCubeShader;
Extonic::LightShader* lightShader;
glm::vec3 coral(1.0f, 1.0f, 1.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

struct TagComponent
{
	std::string Tag;
	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag) : Tag(tag) {}	
};


struct TransformComponent
{
	glm::vec3 _translate;
	glm::vec3 _rotation;
	glm::vec3 _scale;

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(glm::vec3 translate, glm::vec3 rotation, glm::vec3 scale)
		: _translate(translate), _rotation(rotation), _scale(scale) {}
};

struct PointLightComponent
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	PointLightComponent() = default;
	PointLightComponent(const PointLightComponent&) = default;
	PointLightComponent(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float consta, float linea, float quad) 
		: position(pos), ambient(amb), diffuse(diff), specular(spec), constant(consta), linear(linea), quadratic(quad) {}
};

void DummyGame::onInit(GLFWwindow *window)
{
	std::cout << "Initialized" << std::endl;
	//program = new Extonic::ShaderProgram();
	lightShader = new Extonic::LightShader();
	setupAttribs();
	setupLights();

	glfwSetScrollCallback(window, scroll_callback);

	entt::entity entity = m_Registry.create();
	m_Registry.emplace<TagComponent>(entity, "test");

	glEnable(GL_DEPTH_TEST);
}

bool firstMouse = true;

float lastX = 400;
float lastY = 300;

float xoffset;
float yoffset;

void DummyGame::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f),
		glm::vec3(1.3f, -2.0f, -2.5f),
};

PointLight pLight1, pLight2, pLight3, pLight4, pLight5;
SpotLight sLight;
DirLight dLight;

void DummyGame::setupLights()
{
	//lightShader.createShader(Extonic::Util::loadFileAsString("resources/shaders/lightVertex.glsl").c_str(), Extonic::Util::loadFileAsString("resources/shaders/lightFragment.glsl").c_str());
	lightCubeShader.createShader(Extonic::Util::loadFileAsString("resources/shaders/lightCubeVertex.glsl").c_str(), Extonic::Util::loadFileAsString("resources/shaders/lightCubeFragment.glsl").c_str());

	pLight1.position = pointLightPositions[0];
	pLight1.ambient = glm::vec3(0.05f);
	pLight1.diffuse = glm::vec3(0.8f);
	pLight1.specular = glm::vec3(1.0f);
	pLight1.constant = 1.0f;
	pLight1.linear = 0.09f;
	pLight1.quadratic = 0.032f;

	pLight2.position = pointLightPositions[1];
	pLight2.ambient = glm::vec3(0.0f, 1.0f, 0.0f);
	pLight2.diffuse = glm::vec3(0.8f);
	pLight2.specular = glm::vec3(1.0f);
	pLight2.constant = 1.0f;
	pLight2.linear = 0.09f;
	pLight2.quadratic = 0.032f;

	pLight3.position = pointLightPositions[2];
	pLight3.ambient = glm::vec3(0.05f);
	pLight3.diffuse = glm::vec3(0.8f);
	pLight3.specular = glm::vec3(1.0f);
	pLight3.constant = 1.0f;
	pLight3.linear = 0.09f;
	pLight3.quadratic = 0.032f;

	pLight4.position = pointLightPositions[3];
	pLight4.ambient = glm::vec3(0.05f);
	pLight4.diffuse = glm::vec3(0.8f);
	pLight4.specular = glm::vec3(1.0f);
	pLight4.constant = 1.0f;
	pLight4.linear = 0.09f;
	pLight4.quadratic = 0.032f;

	pLight5.position = pointLightPositions[4];
	pLight5.ambient = glm::vec3(0.05f);
	pLight5.diffuse = glm::vec3(0.8f);
	pLight5.specular = glm::vec3(1.0f);
	pLight5.constant = 1.0f;
	pLight5.linear = 0.09f;
	pLight5.quadratic = 0.032f;

	sLight.position = camera.Position;
	sLight.direction = camera.Front;
	sLight.ambient = glm::vec3(0.5f);
	sLight.diffuse = glm::vec3(1.0f);
	sLight.specular = glm::vec3(1.0f);
	sLight.constant = 1.0f;
	sLight.linear = 0.09f;
	sLight.quadratic = 0.032f;
	sLight.cutOff = glm::cos(glm::radians(12.5f));
	sLight.outerCutOff = glm::cos(glm::radians(15.0f));

	dLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	dLight.ambient = glm::vec3(0.05f);
	dLight.diffuse = glm::vec3(0.4f);
	dLight.specular = glm::vec3(0.5f);

	lightShader->addLight(sLight, 0);
	lightShader->addLight(dLight);

	lightShader->addLight(pLight1, 0);
	lightShader->addLight(pLight2, 1);
	lightShader->addLight(pLight3, 2);
	lightShader->addLight(pLight4, 3);
	lightShader->addLight(pLight5, 4);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

float deltaTime = 0;
float lastFrame = 0;

void DummyGame::onUpdate(float delta)
{
	const float cameraSpeed = 2.5f * delta;

	if (Extonic::Input::isKeyPressed(GLFW_KEY_W))
	{
		camera.ProcessKeyboard(Extonic::Camera_Movement::FORWARD, cameraSpeed);
	}

	if (Extonic::Input::isKeyPressed(GLFW_KEY_S))
	{
		camera.ProcessKeyboard(Extonic::Camera_Movement::BACKWARD, cameraSpeed);
	}

	if (Extonic::Input::isKeyPressed(GLFW_KEY_A))
	{
		camera.ProcessKeyboard(Extonic::Camera_Movement::LEFT, cameraSpeed);
	}
	if (Extonic::Input::isKeyPressed(GLFW_KEY_D))
	{
		camera.ProcessKeyboard(Extonic::Camera_Movement::RIGHT, cameraSpeed);
	}
	if (Extonic::Input::isKeyPressed(GLFW_KEY_Q))
	{
		camera.ProcessKeyboard(Extonic::Camera_Movement::UP, cameraSpeed);
	}
	if (Extonic::Input::isKeyPressed(GLFW_KEY_E))
	{
		camera.ProcessKeyboard(Extonic::Camera_Movement::DOWN, cameraSpeed);
	}

	float xpos = Extonic::Input::GetMouseX();
	float ypos = Extonic::Input::GetMouseY();

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

struct Material {
	Extonic::Texture diffuse;
	Extonic::Texture specular;
	Extonic::Texture emissive;
	glm::vec3 emissiveColor;
	float emissiveBrightness;
	float shininess;
};

Material material;
Extonic::Texture specular;
Extonic::Texture emissive;

void DummyGame::onRender()
{
	material.diffuse = texture;
	material.specular = specular;
	material.emissive = emissive;
	material.emissiveColor = glm::vec3(1.0f, 0.5f, 0.31f);
	material.emissiveBrightness = 5.0f;
	material.shininess = 32.0f;

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1);

	glEnable(GL_LIGHTING);

	//program->use();
	lightShader->use();

	lightShader->getShader()->uniform3f("viewPos", camera.Position);
	lightShader->getShader()->uniform1f("material.shininess", material.shininess);
	lightShader->getShader()->uniform1i("material.diffuse", 0);
	lightShader->getShader()->uniform1i("material.specular", 1);
	lightShader->getShader()->uniform1i("material.emission", 2);
	lightShader->getShader()->uniform1f("material.emissiveBrightness", material.emissiveBrightness);

	

	lightShader->updateSpotLight(camera.Position, camera.Front, 0);

	lightShader->updateUniforms();

	texture.bind();

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.1f, 100.0f);

	lightShader->getShader()->matrix4f("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	lightShader->getShader()->matrix4f("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	//lightShader.matrix4f("model", model);
	

	glActiveTexture(GL_TEXTURE0);
	material.diffuse.bind();

	glActiveTexture(GL_TEXTURE1);
	material.specular.bind();

	glActiveTexture(GL_TEXTURE2);
	material.emissive.bind();

	glBindVertexArray(VAO);

	for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++)
	{
		model = glm::translate(model, cubePositions[i]);
		lightShader->getShader()->matrix4f("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, -5, 0));
	model = glm::scale(model, glm::vec3(100.0f, 0.5f, 100.0f));
	lightShader->getShader()->matrix4f("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//float lightX = 2.0f * sin(glfwGetTime());
	//float lightY = 3.0f;
	//float lightZ = 1.5f * cos(glfwGetTime());
	//lightPos = glm::vec3(lightX, lightY, lightZ);

	lightShader->unbind();

	lightCubeShader.use();
	lightCubeShader.matrix4f("projection", projection);
	lightCubeShader.matrix4f("view", view);
	lightCubeShader.uniform3f("lightColor", 1.0f, 1.0f, 1.0f);
	for (unsigned int i = 0; i < 4; i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		lightCubeShader.matrix4f("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	lightCubeShader.unbind();
	//program->unbind();
}

void DummyGame::setupAttribs()
{
  
	/*const char *vertexCode = Extonic::Util::loadShader("resources/shaders/vertex2.vs");
	const char *fragmentCode = Extonic::Util::loadShader("resources/shaders/fragment2.fs");
	program->createShader(vertexCode, fragmentCode); */

	//program->createDefaultShader();
	createMesh();
	createTexture();


	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	

	//program->use();
	//program->matrix4f("model", model);
	//program->matrix4f("view", view);
	//program->unbind();
}

void DummyGame::createMesh()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// Firstly generate the vertex arrays
	glGenVertexArrays(1, &VAO);

	// Then bind the vertex array so we can start applying data to it
	glBindVertexArray(VAO);

	// Generate the vertex buffer object
	glGenBuffers(1, &VBO);

	// Bind the buffer so we can upload the vertices.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Create the buffer data for the size of the vertices then load vertices into it.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Tell the vertex array to look at the vertices, and point to it.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	// Unbind the vertex array.
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void DummyGame::createTexture()
{
	texture.createTexture("container2.png");
	specular.createTexture("container2_specular.png");
	emissive.createTexture("matrix.jpg");
}

DummyGame::~DummyGame()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
