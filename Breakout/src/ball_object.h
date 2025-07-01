#pragma once
#include "game_object.h"

class BallObject : public GameObject
{
public:
	
	float radius_;
	bool is_on_paddle_;

	BallObject(vec2 position, float radius, vec2 velocity, vec3 color, Texture* texture);

	void move(float delta_time, vec2 window_size);
	void reset(vec2 position, vec2 velocity);
};