#version 330 core

in DATA
{
	vec2 texture_coordinates;
} fs_in;

out vec4 fragment_color;

uniform vec3 color_u;
uniform sampler2D texture_u;

void main()
{
	vec3 texture_color = texture(texture_u, fs_in.texture_coordinates).xyz;
	fragment_color = vec4(color_u * texture_color, 1.0f) ;
}