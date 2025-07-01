#include "game_level.h"


GameLevel::GameLevel(Texture* solid_brick, Texture* normal_brick)
	: solid_brick_(solid_brick), normal_brick_(normal_brick)
{ }

void GameLevel::load(const std::string& level_file_path, vec2 starting_position, vec2 level_size)
{
	bricks_.clear();
	std::string file = loadFile(level_file_path.c_str());
	std::vector<std::vector<unsigned int>> bricks(1);
	for (int i = 1, cur = 0; i < file.size(); i += 2)
	{
		bricks[cur].push_back(file[i - 1] - '0');
		if (file[i] == '\n')
		{
			cur++;
			bricks.push_back(std::vector<unsigned int>());
		}
	}


	float brick_height = level_size.y / bricks.size();
	vec2 brick_position = starting_position;
	for (int y = 0; y < bricks.size(); y++)
	{
		brick_position.x = starting_position.x;
		float brick_width = level_size.x / bricks[y].size();
		for (int x = 0; x < bricks[y].size(); x++)
		{

			switch (bricks[y][x])
			{
			case 0:
				break;

			case 1:
				bricks_.push_back(GameObject(brick_position, vec2(brick_width, brick_height), vec3(1.0f), solid_brick_, 0, true));
				break;

			case 2:
				bricks_.push_back(GameObject(brick_position, vec2(brick_width, brick_height), vec3(0.2f, 0.6f, 1.0f), normal_brick_, 0, false));
				break;

			case 3:
				bricks_.push_back(GameObject(brick_position, vec2(brick_width, brick_height), vec3(0.0f, 0.7f, 0.0f), normal_brick_, 0, false));
				break;

			case 4:
				bricks_.push_back(GameObject(brick_position, vec2(brick_width, brick_height), vec3(0.8f, 0.8f, 0.4f), normal_brick_, 0, false));
				break;

			case 5:
				bricks_.push_back(GameObject(brick_position, vec2(brick_width, brick_height), vec3(1.0f, 0.5f, 0.0f), normal_brick_, 0, false));
				break;
			}

			brick_position.x += brick_width;
		}

		brick_position.y -= brick_height;
	}
}

void GameLevel::reLoad()
{
	for (int i = 0; i < bricks_.size(); i++)
	{
		bricks_[i].is_destroyed_ = false;
	}
}

void GameLevel::draw(SpriteRenderer& renderer)
{
	for (int i = 0; i < bricks_.size(); i++)
	{
		bricks_[i].draw(renderer);
	}
}

bool GameLevel::isFinished()
{
	for (int i = 0; i < bricks_.size(); i++)
	{
		if (!bricks_[i].is_solid_)
		{
			if (!bricks_[i].is_destroyed_)
				return false;

		}
	}
	return true;
}