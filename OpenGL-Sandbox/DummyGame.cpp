#include "DummyGame.h"
#include <engine\Utils\Utility.h>
#include <engine\Engine.cpp>
#include <Input.h>

Extonic::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

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
	setupAttribs();

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	entt::entity entity = m_Registry.create();
	m_Registry.emplace<TagComponent>(entity, "test");

	glEnable(GL_DEPTH_TEST);
	
}

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400;
float lastY = 300;
float fov = 45.0f;

float xoffset;
float yoffset;

void DummyGame::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	
	
}

void DummyGame::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
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

void DummyGame::onRender()
{

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1);

	program->use();
	texture.bind();
	glBindVertexArray(VAO);

	glm::mat4 view = camera.GetViewMatrix();

	program->matrix4f("view", view);

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.1f, 100.0f);

	program->matrix4f("projection", projection);

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * glfwGetTime();
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		program->matrix4f("model", model);

		program->uniform4f("color", 1, 1, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	program->unbind();

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
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// Firstly generate the vertex arrays
	glGenVertexArrays(1, &VAO);

	// Then bind the vertex array so we can start applying data to it
	glBindVertexArray(VAO);

	// Generate the vertex buffer object
	glGenBuffers(1, &VBO);

	// Generate the element buffer object
	glGenBuffers(1, &EBO);

	// Bind the buffer so we can upload the vertices.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Create the buffer data for the size of the vertices then load vertices into it.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the element buffer to upload indices.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Create buffer data that's the size of indices, and place indices in it.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
	texture.createTexture("stone_floor.png");

	program->use();
	program->uniform1i("ourTexture", 0);
	program->unbind();
}

DummyGame::~DummyGame()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
