#include "graphics/window.h"

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
	
	if (glewInit() != GLEW_OK)
	{
		Log("Failed to initialize glew\n");
		return -1;
	}

	Log(glGetString(GL_VERSION));
	Log('\n');

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	
	while (!window.isClosed())
	{
		window.setColor(vec4(0.3f, 0.4f, 0.9f, 1.0f));

		if (window.isKeyboardKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		window.clear();
		window.update();
	}

	glfwTerminate();
	return 0;
}