#pragma once
#include<vector>
#include "utils/loading_utils.h"
#include "game_object.h"

class GameLevel
{
public:

	std::vector<GameObject> bricks_;
	Texture* solid_brick_;
	Texture* normal_brick_;

	GameLevel(Texture* solid_brick, Texture* normal_brick);

	void load(const std::string& level_file_path, vec2 starting_position, vec2 level_size);
	void draw(SpriteRenderer& renderer);
	bool isFinished();
};