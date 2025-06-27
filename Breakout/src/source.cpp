#include "graphics/window.h"
#include "utils/timer.h" 
#include "graphics/shader.h"
#include "graphics/texture.h"


#if DEBUG
#define Log(x) std::cout << x

#else
#define Log(x) 

#endif

int main()
{

	if (!glfwInit())
	{
		Log("Failed to initialize glfw\n");
		return -1;
	}
	
	Window window(1024, 675, "breakout");
	window.disableVsync();
	
	if (glewInit() != GLEW_OK)
	{
		Log("Failed to initialize glew\n");
		return -1;
	}

	Log(glGetString(GL_VERSION));
	Log('\n');

	mat4 ortho = orthographic(0, 16, 0, 9, -1, 1);
	Shader shader("res/shaders/triangle.vert", "res/shaders/triangle.frag");
	Texture("res/textures/awesomeface.png");
	shader.enable();
	shader.setMat4f("projection_matrix", ortho);

	float vertices[] =
	{
		1, 1,
		8, 1,
		1, 6
	};

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	Timer timer;
	unsigned int count = 0;
	while (!window.isClosed())
	{
		count++;
		window.setColor(vec4(0.3f, 0.4f, 0.9f, 1.0f));
		window.clear();

		if (window.isKeyboardKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		if (timer.elapsed() > 1.0f)
		{
			printf("%d fps\n", count);
			count = 0;
			timer.reset();
		}
		
		window.update();
	}

	glfwTerminate();
	return 0;
}