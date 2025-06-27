#pragma once
#include "shader.h"
#include "texture.h"

struct Sprite
{
	float rotation_amount_; // in degrees
	vec2 position_;
	vec2 size_;
	vec3 color_;
	Texture* texture_;

	Sprite(vec2 position, vec2 size, vec3 color, float rotation_amount, Texture* texture)
		: position_(position), size_(size), color_(color), rotation_amount_(rotation_amount), texture_(texture)
	{ }
};

class SpriteRenderer
{

	Shader* shader_;

	GLuint vao_, vbo_, ibo_;
public:

	SpriteRenderer(Shader* shader);
	~SpriteRenderer();
	void draw(const Sprite& sprite);
};