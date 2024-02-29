#pragma once
#include "SpriteGo.h"

class SceneGame;

class Melee : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;
	int damage = 0;

	float radius = 50.f;       //반경

	float startAngle;          //시작 각도  :  look - 90  
	float endAngel;            //종료 각도  :  look + 90  


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

