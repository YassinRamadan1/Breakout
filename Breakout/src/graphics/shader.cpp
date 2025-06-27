#include "shader.h"

#ifdef DEBUG
#define Log(x) std::cout << (x)

#else
#define Log(x)

#endif

Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path)
{
	int success;
	char information_log[1000];

	std::string vertex_shader_string = loadFile(vertex_shader_path);
	std::string fragment_shader_string = loadFile(fragment_shader_path);

	const char* vertex_shader_code = vertex_shader_string.c_str();
	const char* fragment_shader_code = fragment_shader_string.c_str();;

	unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vertex_shader_code, nullptr);
	glCompileShader(vertex_shader_id);

	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader_id, 1000, NULL, information_log);
		Log("Vertex Shader Compiling Error!\n");
		Log(information_log);
		Log('\n');
	}

	unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment_shader_id);

	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader_id, 1000, NULL, information_log);
		Log("Fragment Shader Compiling Error!\n");
		Log(information_log);
		Log('\n');
	}

	shader_program_id_ = glCreateProgram();
	glAttachShader(shader_program_id_, vertex_shader_id);
	glAttachShader(shader_program_id_, fragment_shader_id);

	glLinkProgram(shader_program_id_);

	glGetProgramiv(shader_program_id_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program_id_, 1000, NULL, information_log);
		Log("Shader Program Linking Error!\n");
		Log(information_log);
		Log('\n');
	}

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}

Shader::~Shader()
{
	glDeleteProgram(shader_program_id_);
}

void Shader::enable() const
{
	glUseProgram(shader_program_id_);
}

void Shader::disable() const
{
	glUseProgram(0);
}

GLint Shader::getUniformLocation(const GLchar* uniform_name) const
{
	return glGetUniformLocation(shader_program_id_, uniform_name);
}

void Shader::set1iv(const GLchar* uniform_name, unsigned int count, int* v) const
{
	glUniform1iv(getUniformLocation(uniform_name), count, v);
}

void Shader::set1i(const GLchar* uniform_name, GLint v) const
{
	glUniform1i(getUniformLocation(uniform_name), v);
}

void Shader::set1f(const GLchar* uniform_name, GLfloat v) const
{
	glUniform1f(getUniformLocation(uniform_name), v);
}

void Shader::set2f(const GLchar* uniform_name, const vec2& v) const
{
	glUniform2fv(getUniformLocation(uniform_name), 1, (GLfloat*)(&v));
}

void Shader::set3f(const GLchar* uniform_name, const vec3& v) const
{
	glUniform3fv(getUniformLocation(uniform_name), 1, (GLfloat*)(&v));
}

void Shader::set4f(const GLchar* uniform_name, const vec4& v) const
{
	glUniform4fv(getUniformLocation(uniform_name), 1, (GLfloat*)(&v));
}

void Shader::setMat4f(const GLchar* uniform_name, const mat4& v) const
{
	glUniformMatrix4fv(getUniformLocation(uniform_name), 1, false, (GLfloat*)(&v));
}

