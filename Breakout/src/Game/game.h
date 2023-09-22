#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_level.h"
#include "ball_object.h"
#include "particle_generator.h"

// ��Ϸ״̬
enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// ����
enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;// <�Ƿ���ײ����ײ��������ĵ�>

// �����С
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// ��������
const float PLAYER_VELOCITY(500.0f);

// ��ʼ������ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// ��İ뾶
const float BALL_RADIUS = 12.5f;

class Game 
{
public:
	// ��Ϸ״̬
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	// ���졢����
	Game(unsigned int width, unsigned int height);
	~Game();
	// ��ʼ����Ϸ״̬���������е���ɫ���������ؿ���
	void Init();
	// ��Ϸѭ��
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	// �ؿ�
	std::vector<GameLevel> Levels;
	unsigned int Level;
	// �����ײ
	void DoCollisions();
	// ����
	void ResetLevel();
	void ResetPlayer();
};