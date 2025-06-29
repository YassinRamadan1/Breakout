#include "game_object.h"

GameObject::GameObject(vec2 position, vec2 size, vec3 color, Texture* texture, float rotation_amount, bool is_solid)
	: is_solid_(is_solid), rotation_amount_(rotation_amount), position_(position), size_(size), color_(color), texture_(texture)
	{ }

void GameObject::draw(SpriteRenderer& renderer)
{
	renderer.draw(Renderable(position_, size_, color_, rotation_amount_, texture_));
}