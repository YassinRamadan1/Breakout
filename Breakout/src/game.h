#pragma once
#include "graphics/window.h"
#include "game_level.h"
#include "ball_object.h"

const vec2 INITIAL_BALL_VELOCITY(100.0, 350.0);
const vec2 INITIAL_PLAYER_VELOCITY(500.0, 0.0);

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

struct Collision
{
	bool is_collided_;
	Direction collision_direction_;
	vec2 penetration_displacement_;
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

	void addLevels(const char* level_path);
	void init();
	void render();
	void processInput(float delta_time);
	void update(float delta_time);
	Collision collide(BallObject* ball, GameObject* brick);
	void checkCollisions();
	void resetPlayer();
	Direction getClosestDirection(vec2 target);
};