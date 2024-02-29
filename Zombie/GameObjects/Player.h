#pragma once
#include "SpriteGo.h"

class SceneGame;
class Item;
class UiHud;
class Melee;
class Sword;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.f, 0.f };
	float speed = 500.f;

	int maxHp = 1000;
	int hp;
	int maxMagazine = 12;
	int magazine = maxMagazine;
	int ammo = 0;

	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTimer = 0.f;
	float noDamageInterval = 1.f;

	SceneGame* sceneGame = nullptr;
	UiHud* uiHud = nullptr;
	Melee* melee = nullptr;
	Sword* sword = nullptr;


	bool isFiring = false;
	float fireInterval = 0.5f;
	float fireTimer = 0.f;
	float bulletSpeed = 1000.f;
	int bulletDamage = 10;
	
	float MeleeSpeed = 0.5f;     //���� ���� �ӵ�
	int MeleeDamage = 10;          //���� ���� ������

public:
	Player(const std::string& name = "");
	~Player() override = default;

	const int GetPlayerHP() { return hp; }
	const int GetPlayerMaxHP() { return maxHp; }
	const int GetPlayerAmmo() { return ammo; }

	float SetPlayerFireRate(float rateUp) { return fireInterval *= rateUp; }
	int SetPlayerMaxMagazine(int magazineUp) { return maxMagazine += magazineUp; }
	int SetPlayerMaxHP(int hpUp) { return maxHp += hpUp; }
	float SetPlayerSpeed(int speedUp) { return speed += speedUp; }


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();
	void Attack();

	void OnDamage(int damage);
	void OnDie();
	void OnItem(Item* item);
};

