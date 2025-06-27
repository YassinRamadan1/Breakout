#include <iostream>

#include <glew.h>
#include <glfw3.h>

int main()
{

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1024, 675, "breakout", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	
	while (!glfwWindowShouldClose(window))
	{

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}