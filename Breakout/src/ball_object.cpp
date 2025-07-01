#include "ball_object.h"


BallObject::BallObject(vec2 position, float radius, vec2 velocity, vec3 color, Texture* texture)
	: GameObject(position, vec2(2 * radius), color, texture, 0.0f, true), radius_(radius), is_on_paddle_(true)
{ 
	velocity_ = velocity;
}

void BallObject::move(float delta_time, vec2 window_size)
{
	if (is_on_paddle_)
		return;

	position_ += delta_time * velocity_;

	if (position_.x < 0)
	{
		position_.x = 0;
		velocity_.x *= -1;
	}
	
	else if (position_.x + size_.x > window_size.x)
	{
		position_.x = window_size.x - size_.x;
		velocity_.x *= -1;
	}
	
	if (position_.y + size_.y > window_size.y)
	{
		position_.y = window_size.y - size_.y;
		velocity_.y *= -1;
	}
}

void BallObject::reset(vec2 position, vec2 velocity)
{
	is_on_paddle_ = true;
	position_ = position;
	velocity_ = velocity;
}