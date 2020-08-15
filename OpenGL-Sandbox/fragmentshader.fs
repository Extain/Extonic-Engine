#version 330
out vec4 FragColor;

in vec4 ourColor;

uniform vec4 color;

void main()
{
	FragColor = color;
}