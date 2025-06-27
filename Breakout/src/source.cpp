#include "graphics/window.h"
#include "utils/timer.h" 
#include "graphics/sprite_renderer.h"

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
	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	Texture texture("res/textures/awesomeface.png", false);
	shader.enable();
	shader.setMat4f("projection_mat", ortho);

	SpriteRenderer renderer(&shader);
	Sprite sprite(vec2(5, 5), vec2(2, 2), vec3(1.0f), 0.0, &texture);

	Timer timer;
	unsigned int count = 0;
	while (!window.isClosed())
	{
		count++;
		window.setColor(vec4(0.3f, 0.4f, 0.9f, 1.0f));
		window.clear();

		if (window.isKeyboardKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		
		renderer.draw(sprite);

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