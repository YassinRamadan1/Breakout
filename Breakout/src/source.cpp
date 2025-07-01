#include "graphics/window.h"
#include "utils/timer.h" 
#include "graphics/sprite_renderer.h"
#include "game.h"

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

	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	Game breakout(&window, &shader);
	breakout.addLevels("res/levels/one.lvl");

	Timer timer, frame_time;
	float delta_time = 1.0f;
	unsigned int count = 0;

	while (!window.isClosed())
	{
		frame_time.reset();
		count++;
		window.setColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		window.clear();

		breakout.processInput(delta_time);
		breakout.update(delta_time);
		breakout.render();
				
		
		if (timer.elapsed() > 1.0f)
		{
			printf("%d fps\n", count);
			count = 0;
			timer.reset();
		}
		window.update();
		delta_time = frame_time.elapsed();
	}

	glfwTerminate();
	return 0;
}