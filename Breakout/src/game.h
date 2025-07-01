#pragma once
#include "graphics/window.h"
#include "game_level.h"
#include "ball_object.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
	GameState state_;
	unsigned int cur_level_;
	Texture* paddle_;
	Texture* bouncy_ball_;
	Texture* solid_block_;
	Texture* regular_block_;
	Texture* background_;
	Window* window_;
	SpriteRenderer* renderer_;
	Shader* shader_;
	std::vector<GameLevel*> levels_;
	GameObject* player_;
	BallObject* ball_;
public:

	Game(Window* window, Shader* shader);
	~Game();

	void addTexture(const char* texture_path);
	void addLevels(const char* level_path);
	void init();
	void render();
	void processInput(float delta_time);
	void update(float delta_time);
	bool collide(BallObject* ball, GameObject* brick);
	void checkCollisions();
};