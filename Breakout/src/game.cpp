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
	player_->velocity_.x = 500.0f;

	ball_ = new BallObject(player_->position_ + vec2(player_->size_.x / 2.0f, player_->size_.y) , 12.5, vec2(100.0, 350.0), vec3(1.0f), bouncy_ball_);

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
	if (ball_->is_on_paddle_ || ball_->position_.y < 0)
		ball_->reset(player_->position_ + vec2(player_->size_.x / 2.0f, player_->size_.y), vec2(100.0, 350.0));
	checkCollisions();
}

bool Game::collide(BallObject* ball, GameObject* brick)
{
	vec2 brick_half_size = brick->size_ / 2.0;
	vec2 ball_center = ball->position_ + (ball->size_ / 2.0);
	vec2 brick_center = brick->position_ + brick_half_size;

	vec2 direction = ball_center - brick_center;
	direction.x = std::max(-brick_half_size.x, std::min(direction.x, brick_half_size.x));
	direction.y = std::max(-brick_half_size.y, std::min(direction.y, brick_half_size.y));
	vec2 closest_point = brick_center + direction;

	return length2(closest_point - ball_center) <= ball->radius_ * ball->radius_;
}

void Game::checkCollisions()
{
	std::vector<GameObject>& level = levels_[cur_level_]->bricks_;

	for (int i = 0; i < level.size(); i++)
	{
		if (level[i].is_destroyed_)
			continue;
		if (collide(ball_, &level[i]))
		{

			if (!level[i].is_solid_)
				level[i].is_destroyed_ = true;
		}
	}
}