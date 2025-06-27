#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "../math/math.h"

#define MAX_KEYS	350
#define MAX_BUTTONS 8

class Window
{
	GLFWwindow* window_;
	unsigned int width_, height_;

	bool keyboard_keys_[MAX_KEYS];
	bool mouse_buttons_[MAX_BUTTONS];
	double mouse_x_position_, mouse_y_position_;
public:

	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	void setColor(vec4 color) const;
	void close() const;
	bool isClosed() const;
	void clear() const;
	void update() const;
	bool isKeyboardKeyPressed(int key_code) const;
	bool isMouseButtonPressed(int button_code) const;
	vec2 getMousePosition() const;
	void enableVsync() const;
	void disableVsync() const;
private:

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyboardKeyCallback(GLFWwindow* window, int key_code, int scan_code, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button_code, int action, int mods);
	static void mousePositionCallback(GLFWwindow* window, double x_position, double y_position);
};