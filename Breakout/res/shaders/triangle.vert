#version 330 core

layout (location = 0) in vec2 position_in;

uniform mat4 projection_matrix;

void main()
{
	gl_Position = projection_matrix * vec4(position_in, 0.0, 1.0f);
}