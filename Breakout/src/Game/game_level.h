#pragma once

#include "game_object.h"
#include "resource_manager.h"
#include <vector>

class GameLevel
{
public:
	// �ؿ�״̬
	std::vector<GameObject> Bricks;
	GameLevel() {};
	// ���ļ����عؿ�
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	// ��Ⱦ�ؿ�
	void Draw(SpriteRenderer& renderer);
	bool IsCompleted();
private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};