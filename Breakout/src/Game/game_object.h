#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class GameObject
{
public:
	// ÎïÌå×´Ì¬
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool IsSolid;
	bool Destroyed;
	// äÖÈ¾×´Ì¬
	Texture2D Sprite;
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// »æÖÆ
	virtual void Draw(SpriteRenderer& renderer);
};