#version 330 core

layout (location = 0) in vec2 vertex_in;

out DATA
{
	vec2 texture_coordinates;
} vs_out;

uniform mat4 projection_mat;
uniform mat4 model_mat;

void main()
{
	vs_out.texture_coordinates = vertex_in.xy;

	gl_Position = projection_mat * model_mat * vec4(vertex_in.xy, 0.0f, 1.0f);
}
