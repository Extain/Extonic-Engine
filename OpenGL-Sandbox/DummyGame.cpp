#include "DummyGame.h"
#include <glad\gl.h>
#include <GLFW\glfw3.h>



void DummyGame::onInit()
{
	std::cout << "Initialized" << std::endl;
	program = new Extonic::ShaderProgram();
	setupAttribs();
}

void DummyGame::onUpdate(float delta)
{

}

void DummyGame::onRender()
{
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1);

	program->use();
	glBindVertexArray(VAO);

	glUniform4f(vertexColorLoc, greenValue, greenValue, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	program->unbind();

}

void DummyGame::setupAttribs()
{
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glGenVertexArrays(1, &VAO);
	//LOGGER->Log("Generating vertex arrays to ID: %s", VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	//LOGGER->Log("Binding buffer to ID: %s", VBO);

	glGenBuffers(1, &EBO);
	//LOGGER->Log("Generating element buffer object to ID: %s", EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//LOGGER->Log("Uploading data to buffer, size: %s", sizeof(vertices));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//LOGGER->Log("Uploading data to element buffer, size: %s", sizeof(indices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	vertexColorLoc = glGetUniformLocation(program->shaderID, "color");
}

DummyGame::~DummyGame()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
