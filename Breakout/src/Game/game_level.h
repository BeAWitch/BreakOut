#pragma once

#include "game_object.h"
#include "resource_manager.h"
#include <vector>

class GameLevel
{
public:
	// 关卡状态
	std::vector<GameObject> Bricks;
	GameLevel() {};
	// 从文件加载关卡
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	// 渲染关卡
	void Draw(SpriteRenderer& renderer);
	bool IsCompleted();
private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};