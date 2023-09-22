#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_level.h"
#include "ball_object.h"
#include "particle_generator.h"

// 游戏状态
enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// 方向
enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;// <是否碰撞，碰撞方向，最近的点>

// 挡板大小
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// 挡板速率
const float PLAYER_VELOCITY(500.0f);

// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// 球的半径
const float BALL_RADIUS = 12.5f;

class Game 
{
public:
	// 游戏状态
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	// 构造、析构
	Game(unsigned int width, unsigned int height);
	~Game();
	// 初始化游戏状态（加载所有的着色器、纹理、关卡）
	void Init();
	// 游戏循环
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	// 关卡
	std::vector<GameLevel> Levels;
	unsigned int Level;
	// 检测碰撞
	void DoCollisions();
	// 重置
	void ResetLevel();
	void ResetPlayer();
};