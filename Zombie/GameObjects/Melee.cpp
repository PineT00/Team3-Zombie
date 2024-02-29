#include "pch.h"
#include "Melee.h"
#include "Player.h"
#include "SceneGame.h"
#include "Zombie.h"

Melee::Melee(const std::string& name)
	:SpriteGo(name)
{
}

void Melee::MeleeAttack(float angle, float t, int d)
{
	currentAngle = angle + 90;
	endAngle = angle - 90;
	SetPosition(player->GetPosition() + sf::Vector2f(std::cosf(currentAngle) * radius, std::sinf(currentAngle) * radius));
	angleSpeed = 180.f / t;
	damage = d;
}

void Melee::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/ball.png");
	SetOrigin(Origins::MR);
	
	hasHitBox = true;
}

void Melee::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

}

void Melee::Update(float dt)
{
	currentAngle -= angleSpeed * dt;
	
	sf::Vector2f pos = player->GetPosition() + sf::Vector2f(std::cosf(currentAngle)* radius, std::sinf(currentAngle)* radius);
	SetPosition(pos);
	SetRotation(currentAngle);
	if (currentAngle < endAngle)
	{
		SetActive(false);

	}
}

void Melee::FixedUpdate(float dt)
{
	const std::list<GameObject*>& list = sceneGame->GetZombieList();
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			

			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if (zombie != nullptr)
				zombie->OnDamage(damage);

			break;
		}
	}
}
