#include "pch.h"
#include "Melee.h"

Melee::Melee(const std::string& name)
	:SpriteGo(name)
{
}

void Melee::MeleeAttack(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;
}

void Melee::Init()
{
}

void Melee::Reset()
{
}

void Melee::Update(float dt)
{
}

void Melee::FixedUpdate(float dt)
{
}
