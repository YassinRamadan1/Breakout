#include "window.h"

#if DEBUG
#define Log(x) std::cout << x

#else
#define Log(x) 

#endif

Window::Window(unsigned int width, unsigned int height, const char* title)
	: width_(width), height_(height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(width_, height_, title, nullptr, nullptr);

	if (!window_)
	{
		Log("Failed to create a window\n");
		glfwTerminate();

		return;
	}
	
	glfwMakeContextCurrent(window_);

	glfwSetWindowUserPointer(window_, this);
	glViewport(0, 0, width_, height_);
	glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);
	glfwSetKeyCallback(window_, keyboardKeyCallback);
	glfwSetMouseButtonCallback(window_, mouseButtonCallback);
	glfwSetCursorPosCallback(window_, mousePositionCallback);
	
	memset(keyboard_keys_, 0, MAX_KEYS);
	memset(mouse_buttons_, 0, MAX_BUTTONS);
}

Window::~Window()
{
	glfwDestroyWindow(window_);
}

void Window::close() const
{
	glfwSetWindowShouldClose(window_, true);
}

bool Window::isClosed() const
{
	return glfwWindowShouldClose(window_);
}

void Window::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update() const
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Log(error);
		Log('\n');
	}
	glfwSwapBuffers(window_);
	glfwPollEvents();
}

void Window::setColor(vec4 color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
}

bool Window::isKeyboardKeyPressed(int key_code) const
{
	return keyboard_keys_[key_code];
}

bool Window::isMouseButtonPressed(int button_code) const
{
	return mouse_buttons_[button_code];
}

vec2 Window::getMousePosition() const
{
	return vec2(mouse_x_position_, mouse_y_position_);
}

void Window::enableVsync() const
{
	glfwSwapInterval(1);
}

void Window::disableVsync() const
{
	glfwSwapInterval(0);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->width_ = width, win->height_ = height;
	glViewport(0, 0, width, height);
}

void Window::keyboardKeyCallback(GLFWwindow* window, int key_code, int scan_code, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->keyboard_keys_[key_code] = (action != GLFW_RELEASE);
}

void Window::mouseButtonCallback(GLFWwindow* window, int button_code, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->mouse_buttons_[button_code] = (action != GLFW_RELEASE);
}

void Window::mousePositionCallback(GLFWwindow* window, double x_position, double y_position)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->mouse_x_position_ = x_position, win->mouse_y_position_ = y_position;
}