#version 330
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform vec4 color;
uniform sampler2D ourTexture;

void main()
{
FragColor = texture(ourTexture, TexCoord) * color;
}