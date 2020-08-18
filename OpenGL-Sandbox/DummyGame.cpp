#include "DummyGame.h"
#include <engine\Utils\Utility.h>
#include <engine\Engine.cpp>
#include <Input.h>

Extonic::PerspectiveCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Extonic::ShaderProgram lightShader, lightCubeShader;
glm::vec3 coral(1.0f, 1.0f, 1.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

const char* lightVertex = {
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aNormal; \n"
	"layout (location = 2) in vec2 aTexCoord; \n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"out vec3 Normal; \n"
	"out vec3 FragPos; \n"
	"out vec2 TexCoord; \n"
	"void main()\n"
	"{\n"
	"gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
	"FragPos = vec3(model * vec4(aPos, 1.0)); \n"
	"Normal = mat3(transpose(inverse(model))) * aNormal; \n"
	"TexCoord = aTexCoord; \n"
	"}\0"
};

const char* lightFragment = {
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 Normal; \n"
	"in vec3 FragPos; \n"
	"in vec2 TexCoord; \n"
	"uniform vec3 objectColor;\n"
	"uniform vec3 lightColor;\n"
	"uniform vec3 lightPos; \n"
	"uniform vec3 viewPos; \n"
	"uniform float time; \n"
	"struct Material {\n"
	"sampler2D diffuse; \n"
	"sampler2D specular; \n"
	"sampler2D emission; \n"
	"float shininess; \n"
	"};\n"
	"struct Light {\n"
	"vec3 position; \n"
	"vec3 ambient; \n"
	"vec3 diffuse; \n"
	"vec3 specular; \n"
	"};\n"
	"uniform Material material; \n"
	"uniform Light light; \n"
	"vec3 calculate_emission() \n"
	"{\n"
	"vec3 show = step(vec3(1.0), vec3(1.0) - texture(material.specular, TexCoord).rgb);\n"
	"return texture(material.emission, TexCoord).rgb * show; \n"
	"}\n"
	"void main()\n"
	"{\n"
	"float specularStrength = 0.5; \n"
	"float ambientStrength = 0.8; \n"
	"vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord)); \n"
	"vec3 norm = normalize(Normal); \n"
	"vec3 lightDir = normalize(lightPos - FragPos); \n"
	"float diff = max(dot(norm, lightDir), 0.0); \n"
	"vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)); \n"
	"vec3 viewDir = normalize(viewPos - FragPos); \n"
	"vec3 reflectDir = reflect(-lightDir, norm); \n"
	"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); \n"
	"vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));\n"
	"vec3 emission = calculate_emission(); \n"
	"emission = emission * (sin(time) * 0.5 + 0.5) * 2.0; \n"
	"vec3 result = ambient + diffuse + specular + emission;\n"
	"FragColor = vec4(result, 1.0);\n"
	"}\0"
	

};

const char* lightCubeVertex = {
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"void main()\n"
	"{\n"
	"gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
	"}\0"
};

const char* lightCubeFragment = {
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec3 lightColor; \n"
	"void main()\n"
	"{\n"
	"FragColor = vec4(lightColor, 1.0);\n"
	"}\0"
};

struct TagComponent
{
	std::string Tag;
	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag) : Tag(tag) {}	
};

void DummyGame::onInit(GLFWwindow *window)
{
	std::cout << "Initialized" << std::endl;
	program = new Extonic::ShaderProgram();
	setupLights();
	setupAttribs();

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

void DummyGame::setupLights()
{
	lightShader.createShader(lightVertex, lightFragment);
	lightCubeShader.createShader(lightCubeVertex, lightCubeFragment);

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

	float shininess;
};

struct Light {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

Material material;
Light light;
Extonic::Texture specular;
Extonic::Texture emissive;

void DummyGame::onRender()
{
	material.diffuse = texture;
	material.specular = specular;
	material.emissive = emissive;
	material.shininess = 64.0f;

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1);


	//program->use();
	lightShader.use();
	lightShader.uniform3f("objectColor", coral);
	lightShader.uniform3f("lightColor", lightColor);
	lightShader.uniform3f("lightPos", lightPos);
	lightShader.uniform3f("viewPos", camera.Position);
	lightShader.uniform1f("material.shininess", material.shininess);
	lightShader.uniform1i("material.diffuse", 0);
	lightShader.uniform1i("material.specular", 1);
	lightShader.uniform1i("material.emission", 2);

	lightShader.uniform1f("time", glfwGetTime());

	/*lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);*/

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.5f);

	light.ambient = ambientColor;
	light.diffuse = diffuseColor;
	light.specular = glm::vec3(1.0f);

	lightShader.uniform3f("light.ambient", light.ambient);
	lightShader.uniform3f("light.diffuse", light.diffuse);
	lightShader.uniform3f("light.specular", light.specular);
	texture.bind();

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.1f, 100.0f);

	lightShader.matrix4f("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	lightShader.matrix4f("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	lightShader.matrix4f("model", model);

	glActiveTexture(GL_TEXTURE0);
	material.diffuse.bind();

	glActiveTexture(GL_TEXTURE1);
	material.specular.bind();

	glActiveTexture(GL_TEXTURE2);
	material.emissive.bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	float lightX = 2.0f * sin(glfwGetTime());
	float lightY = 0.0f;
	float lightZ = 1.5f * cos(glfwGetTime());
	lightPos = glm::vec3(lightX, lightY, lightZ);

	lightCubeShader.use();
	lightCubeShader.matrix4f("projection", projection);
	lightCubeShader.matrix4f("view", view);
	lightCubeShader.uniform3f("lightColor", lightColor);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	lightCubeShader.matrix4f("model", model);

	//glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	lightCubeShader.unbind();
	//program->unbind();
}

void DummyGame::setupAttribs()
{
  
	/*const char *vertexCode = Extonic::Util::loadShader("resources/shaders/vertex2.vs");
	const char *fragmentCode = Extonic::Util::loadShader("resources/shaders/fragment2.fs");
	program->createShader(vertexCode, fragmentCode); */

	program->createDefaultShader();
	createMesh();
	createTexture();


	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	

	program->use();
	program->matrix4f("model", model);
	program->matrix4f("view", view);
	program->unbind();
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
