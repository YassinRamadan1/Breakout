#include "game.h"

Game::Game(Window* window, Shader* shader)
:	window_(window), shader_(shader)
{
	renderer_ = new SpriteRenderer(shader_);
	
	background_ = new Texture("res/textures/background.jpg");
	paddle_ = new Texture("res/textures/paddle.png");
	bouncy_ball_ = new Texture("res/textures/ball.png");
	solid_block_ = new Texture("res/textures/block_solid.png");
	regular_block_ = new Texture("res/textures/block.png");
	
	player_ = new GameObject(vec2(window_->getWidth() / 2.0f, window_->getHeight() / 20.0f), vec2(100.0f, 20.0f), vec3(1.0f), paddle_, 0.0f, true);
	player_->velocity_ = INITIAL_PLAYER_VELOCITY;

	ball_ = new BallObject(player_->position_ + vec2(player_->size_.x / 2.0f, player_->size_.y) , 12.5, INITIAL_BALL_VELOCITY, vec3(1.0f), bouncy_ball_);

	shader_->enable();
	shader_->setMat4f("projection_mat", orthographic(0, window_->getWidth(), 0, window_->getHeight(), -1, 1));
	cur_level_ = 0;
}

Game::~Game()
{
	delete renderer_;

	delete paddle_;
	delete bouncy_ball_;
	delete solid_block_;
	delete regular_block_;
	delete background_;

	delete player_;
	delete ball_;
}

void Game::addLevels(const char* level_path)
{
	levels_.push_back(new GameLevel(solid_block_, regular_block_));
	GameLevel*& level = levels_.back();

	level->load(level_path, vec2(0, window_->getHeight()), vec2(window_->getWidth(), window_->getHeight() / 2));
}

void Game::render()
{

	if (state_ == GAME_ACTIVE)
	{
		renderer_->draw(Renderable(vec2(0, 0), vec2(window_->getWidth(), window_->getHeight()), vec3(1.0f), 0, background_));
		player_->draw(*renderer_);
		ball_->draw(*renderer_);
		levels_[cur_level_]->draw(*renderer_);
	}
}

void Game::processInput(float delta_time)
{
	if (state_ == GAME_ACTIVE)
	{
		vec2 velocity = delta_time * player_->velocity_;
		if (window_->isKeyboardKeyPressed(GLFW_KEY_A))
		{
			player_->position_ -= velocity;
			if (player_->position_.x < 0)
				player_->position_.x = 0;
		}
		if (window_->isKeyboardKeyPressed(GLFW_KEY_D))
		{
			player_->position_ += velocity;
			if (player_->position_.x + player_->size_.x > window_->getWidth())
				player_->position_.x = window_->getWidth() - player_->size_.x;
		}

		if (window_->isKeyboardKeyPressed(GLFW_KEY_SPACE))
		{
			ball_->is_on_paddle_ = false;
		}
	}
}

void Game::update(float delta_time)
{
	ball_->move(delta_time, vec2(window_->getWidth(), window_->getHeight()));
	if (ball_->is_on_paddle_)
	{
		ball_->reset(player_->position_ + vec2(player_->size_.x / 2.0f, player_->size_.y), INITIAL_BALL_VELOCITY);
	}
	if (ball_->position_.y < 0)
	{
		levels_[cur_level_]->reLoad();
		resetPlayer();
		ball_->reset(player_->position_ + vec2(player_->size_.x / 2.0f, player_->size_.y), INITIAL_BALL_VELOCITY);
	}
	checkCollisions();
}

void Game::resetPlayer()
{
	player_->position_ = vec2(window_->getWidth() / 2.0f, window_->getHeight() / 20.0f);
	player_->velocity_ = INITIAL_PLAYER_VELOCITY;
}

Direction Game::getClosestDirection(vec2 target)
{
	vec2 vec(1.0f, 0.0f);
	Direction closest = RIGHT;
	float max = dot(vec, target), current;

	vec.x = -1.0f, vec.y = 0.0f;
	current = dot(vec, target);
	if (max < current)
		closest = LEFT, max = current;

	vec.x = 0.0f, vec.y = 1.0f;
	current = dot(vec, target);
	if (max < current)
		closest = UP, max = current;

	vec.x = 0.0f, vec.y = -1.0f;
	current = dot(vec, target);
	if (max < current)
		closest = DOWN, max = current;

	return closest;
}

Collision Game::collide(BallObject* ball, GameObject* brick)
{
	Collision collision;

	vec2 ball_center = ball->position_ + (ball->size_ / 2.0);
	vec2 brick_center = brick->position_ + (brick->size_ / 2.0);

	vec2 closest_point(std::max(brick->position_.x, std::min( ball_center.x, brick->position_.x + brick->size_.x)),
		std::max(brick->position_.y, std::min(ball_center.y, brick->position_.y + brick->size_.y)));

	vec2 displacement_direction = ball_center - closest_point;
	float len = length(displacement_direction);

	collision.is_collided_ = len <= ball->radius_;
	if (!collision.is_collided_)
		return collision;

	collision.penetration_displacement_ = (len < 1e-8) ? vec2(1.0f, 0.0f) : (displacement_direction / len);
	collision.penetration_displacement_ = (ball->radius_ - len) * collision.penetration_displacement_;
	collision.collision_direction_ = getClosestDirection(collision.penetration_displacement_);
	
	return collision;
}

void Game::checkCollisions()
{
	std::vector<GameObject>& level = levels_[cur_level_]->bricks_;

	for (int i = 0; i < level.size(); i++)
	{
		if (level[i].is_destroyed_)
			continue;
		Collision collision = collide(ball_, &level[i]);
		if (collision.is_collided_)
		{
			ball_->position_ += collision.penetration_displacement_;

			switch (collision.collision_direction_)
			{
			case RIGHT:
				ball_->velocity_.x = 1.0 * abs(ball_->velocity_.x);
				break;
			case LEFT:
				ball_->velocity_.x = -1.0 * abs(ball_->velocity_.x);
				break;
			case UP:
				ball_->velocity_.y = 1.0 * abs(ball_->velocity_.y);
				break;
			case DOWN:
				ball_->velocity_.y = -1.0 * abs(ball_->velocity_.y);
				break;
			}

			if (!level[i].is_solid_)
				level[i].is_destroyed_ = true;
		}
	}
	if(!ball_->is_on_paddle_)
	{
		Collision collision = collide(ball_, player_);
		if (!collision.is_collided_)
			return;
	
		ball_->position_ += collision.penetration_displacement_;

		switch (collision.collision_direction_)
		{
		case RIGHT:
			ball_->velocity_.x = 1.0 * abs(ball_->velocity_.x);
			break;
		case LEFT:
			ball_->velocity_.x = -1.0 * abs(ball_->velocity_.x);
			break;
		case UP:
			{
				float distance = (ball_->position_.x + ball_->radius_) - (player_->position_.x + player_->size_.x / 2.0f);
				float percentage = distance / (player_->size_.x / 2.0f);
				float old = length(ball_->velocity_);
				float strength = 2.0f;
				ball_->velocity_.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
				ball_->velocity_.y = 1.0 * abs(ball_->velocity_.y);
				ball_->velocity_ = old * normalize(ball_->velocity_);
				break;
			}
		}
	}

}