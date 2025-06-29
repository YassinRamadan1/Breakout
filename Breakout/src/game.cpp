#include "game.h"

Game::Game(Window* window, Shader* shader)
:	window_(window), shader_(shader)
{
	renderer_ = new SpriteRenderer(shader_);
	
	background_ = new Texture("res/textures/background.jpg");
	paddle_ = new Texture("res/textures/paddle.png");
	bouncy_ball_ = new Texture("res/textures/paddle.png");
	solid_block_ = new Texture("res/textures/block_solid.png");
	regular_block_ = new Texture("res/textures/block.png");
	
	player_ = new GameObject(vec2(window_->getWidth() / 2.0f, window_->getHeight() / 20.0f), vec2(100.0f, 20.0f), vec3(1.0f), paddle_, 0.0f, true);
	player_->velocity.x = 500.0f;

	ball_ = new GameObject();

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
		//ball_->draw(*renderer_);
		levels_[cur_level_]->draw(*renderer_);
	}
}

void Game::processInput(float delta_time)
{
	if (state_ == GAME_ACTIVE)
	{
		vec2 velocity = delta_time * player_->velocity;
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
	}
}