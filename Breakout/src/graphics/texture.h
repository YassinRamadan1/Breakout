#pragma once
#include <glew.h>
#include "../utils/loading_utils.h"

class Texture
{

	GLuint texture_id_;
public:

	Texture(const std::string& image_path, bool vertical_flip = true, bool gamma_space = true);
	~Texture();

	void bind() const;
	void unbind() const;
};