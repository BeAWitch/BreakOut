#include "game.h"

SpriteRenderer* Renderer;
GameObject* Player;
BallObject* Ball;
ParticleGenerator* Particles;

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}


void Game::Init()
{
	// 加载着色器
	ResourceManager::LoadShader("src/Game/Shader/shader.vs", "src/Game/Shader/shader.frag", nullptr, "sprite");
	ResourceManager::LoadShader("src/Game/Shader/particle.vs", "src/Game/Shader/particle.frag", nullptr, "particle");
	// 配置着色器
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	// 设置专用于渲染的控制
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	
	// 加载纹理
	ResourceManager::LoadTexture("src/Game/Texture/background.jpg", false, "background");
	ResourceManager::LoadTexture("src/Game/Texture/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("src/Game/Texture/block.png", false, "block");
	ResourceManager::LoadTexture("src/Game/Texture/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("src/Game/Texture/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("src/Game/Texture/particle.png", true, "particle");
	// 加载关卡
	GameLevel one; 
	one.Load("src/Game/Level/one.lvl", this->Width, this->Height / 2);
	GameLevel two; 
	two.Load("src/Game/Level/two.lvl", this->Width, this->Height / 2);
	GameLevel three; 
	three.Load("src/Game/Level/three.lvl", this->Width, this->Height / 2);
	GameLevel four; 
	four.Load("src/Game/Level/four.lvl", this->Width, this->Height / 2);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;
	// 设置挡板
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	// 球
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
	// 粒子
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 800);
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// 移动挡板
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			Ball->Stuck = false;
		}
	}
}

void Game::Update(float dt)
{
	Ball->Move(dt, this->Width);
	// 检测碰撞
	this->DoCollisions();
	// 更新粒子
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));
	// 检查球是否触底，触底后重置游戏
	if (Ball->Position.y >= this->Height)
	{
		this->ResetLevel();
		this->ResetPlayer();
	}
}

void Game::ResetLevel()
{
	if (this->Level == 0)
		this->Levels[0].Load("src/Game/Level/one.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 1)
		this->Levels[1].Load("src/Game/Level/two.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 2)
		this->Levels[2].Load("src/Game/Level/three.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 3)
		this->Levels[3].Load("src/Game/Level/four.lvl", this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
	// 重置球
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// 绘制背景
		Renderer->DrawSprite(ResourceManager::GetTexture("background"),
			glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
		// 绘制关卡
		this->Levels[this->Level].Draw(*Renderer);
		// 绘制挡板
		Player->Draw(*Renderer);
		// 绘制粒子,绘制在球体后，其他物体前
		Particles->Draw();
		// 绘制球
		Ball->Draw(*Renderer);
	}
}

Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),  // 上
		glm::vec2(1.0f, 0.0f),  // 右
		glm::vec2(0.0f, -1.0f), // 下
		glm::vec2(-1.0f, 0.0f)  // 左
	};
	float max = 0.0f;
	int best_match = -1;
	for (int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

Collision CheckCollision(BallObject& one, GameObject& two)
{
	// 获取圆的中心 
	glm::vec2 center(one.Position + one.Radius);
	// 计算AABB的信息（中心、半边长）
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;
	
	if (glm::length(difference) <= one.Radius)
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

void Game::DoCollisions()
{
	for (auto& box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision))
			{
				if (!box.IsSolid)
					box.Destroyed = true;
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT) // 水平方向
				{
					Ball->Velocity.x = -Ball->Velocity.x; // 反转水平方向
					// 重定位
					float penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						Ball->Position.x += penetration; // 右移
					else
						Ball->Position.x -= penetration; // 左移
				}
				else // 竖直方向
				{
					Ball->Velocity.y = -Ball->Velocity.y; // 反转竖直方向
					// 重定位
					float penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
						Ball->Position.y -= penetration; // 上移
					else
						Ball->Position.y += penetration; // 下移
				}
			}
		}
	}
	// 球和挡板
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		// 检查碰到了挡板的哪个位置，并根据碰到哪个位置来改变速度
		float centerBoard = Player->Position.x + Player->Size.x / 2;
		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2);
		// 依据结果移动
		float strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;// 旧速度
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		Ball->Velocity.y = -1 * abs(Ball->Velocity.y);// 防止球中心进入挡板内而导致的粘板，直接返回负的竖直速度
		// 水平方向的速度大小变化，竖直方向没变，合速度变化
		// 所以将新速度正交化再乘旧速度的大小
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
	}
}