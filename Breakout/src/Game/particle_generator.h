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
	// ������������
	void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	// ��Ⱦ
	void Draw();
private:
	// ״̬
	std::vector<Particle> particles;
	unsigned int amount;
	// ��Ⱦ״̬
	Shader shader;
	Texture2D texture;
	unsigned int VAO;
	// ��ʼ��
	void Init();
	// �ҵ���һ������������
	unsigned int firstUnusedParticle();
	// ��������
	void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};