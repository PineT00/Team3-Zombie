#pragma once
#include "SpriteGo.h"

class SceneGame;

class Melee : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;
	int damage = 0;

	SceneGame* sceneGame;
public:
	Melee(const std::string& name = "");
	~Melee() override = default;

	void MeleeAttack(const sf::Vector2f& dir, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

};

