#pragma once
#include "SpriteGo.h"
#include "Player.h"

class SceneGame;
class UiHud;
class ItemSpawner;

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
		Worm,
	};
	static const int TotalTypes = 3;
	static Zombie* Create(Types zombieType);

protected:
	Types type;

	sf::Vector2f look = { 1.f, 0.f };

	int damage;
	float attackInterval;
	float attackTimer = 0.f;

	int maxHp;
	float speed;
	int hp;

	bool isDash = false;
	float dashSpeed;
	float originalSpeed;

	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
	UiHud* uiHud = nullptr;
	ItemSpawner* itemSpawner = nullptr;

	sf::Vector2f direction;
	bool isAlive = true;

	float dashInterval = 3.f;
	float dashTimer = 0.f;
	float dashTime = 1.f;


	Zombie(const std::string& name = ""); // 외부에서 좀비를 생성 못하도록

public:
	~Zombie() override = default;

	void Dash(bool isDash);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	void OnDamage(int damage);
	void OnDie();
};

