#pragma once
#include "math/math.h"
#include "graphics/sprite_renderer.h"

class GameObject
{
public:

	bool is_destroyed_ = false;
	bool is_solid_;
	float rotation_amount_; // in degrees
	vec2 position_;
	vec2 size_;
	vec2 velocity = vec2(0.0f, 0.0f);
	vec3 color_;
	Texture* texture_;

	GameObject() { }
	GameObject(vec2 position, vec2 size, vec3 color, Texture* texture, float rotation_amount, bool is_solid);

	void draw(SpriteRenderer& renderer);
};