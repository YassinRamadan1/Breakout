#pragma once
#include <glew.h>
#include "../utils/loading_utils.h"
#include "../math/math.h"

class Shader
{
	GLuint shader_program_id_ = 0;

	GLint getUniformLocation(const GLchar* uniform_name) const;
public:

	Shader(const char* vertex_shader_path, const char* fragment_shader_path);
	~Shader();

	void enable() const;
	void disable() const;

	void set1iv(const GLchar* uniform_name, unsigned int count, int* v) const;
	void set1i(const GLchar* uniform_name, GLint v) const;
	void set1f(const GLchar* uniform_name, GLfloat v) const;

	void set2f(const GLchar* uniform_name, const vec2& v) const;
	void set3f(const GLchar* uniform_name, const vec3& v) const;
	void set4f(const GLchar* uniform_name, const vec4& v) const;

	void setMat4f(const GLchar* uniform_name, const mat4& v) const;
};