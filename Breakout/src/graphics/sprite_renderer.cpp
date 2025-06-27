#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader* shader)
	: shader_(shader)
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	// writing the fixed positions and texture coordinates
	GLfloat vertices[] =
	{
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0
	};

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)(0));
	glEnableVertexAttribArray(0);
	
	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(1, &ibo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ibo_);
}

void SpriteRenderer::draw(const Sprite& sprite)
{
	mat4 model = scale(vec3(sprite.size_.x, sprite.size_.y, 0));

	model = translate(vec3(sprite.position_.x + sprite.size_.x / 2, sprite.position_.y + sprite.size_.y / 2, 0)) *
		rotate(radians(sprite.rotation_amount_), vec3(0.0f, 0.0f, 1.0f)) *
		translate(vec3(-sprite.size_.x / 2, -sprite.size_.y / 2, 0)) * model;
	
	shader_->enable();
	shader_->set1i("texture_u", 0);
	shader_->set3f("color_u", sprite.color_);	
	shader_->setMat4f("model_mat", model);

	glActiveTexture(GL_TEXTURE0);
	sprite.texture_->bind();

	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}