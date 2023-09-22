#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"
#include "game_object.h"

#include <vector>

struct Particle
{
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	float Life;
	Particle() 
		: Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) {};
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
	// 更新所有粒子
	void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	// 渲染
	void Draw();
private:
	// 状态
	std::vector<Particle> particles;
	unsigned int amount;
	// 渲染状态
	Shader shader;
	Texture2D texture;
	unsigned int VAO;
	// 初始化
	void Init();
	// 找到第一个消亡的粒子
	unsigned int firstUnusedParticle();
	// 粒子重生
	void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};