#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "UiHud.h"
#include "SpriteGoEffect.h"
#include "ZombieTable.h"
#include "ItemSpawner.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("Zombie");
	zombie->type = zombieType;

	const DataZombie& data = ZOMBIE_TABLE->Get(zombieType);
	zombie->textureId = data.textureId;
	zombie->maxHp = data.maxHp;
	zombie->speed = data.speed;
	zombie->damage = data.damage;
	zombie->attackInterval = data.attackInterval;
	zombie->sortLayer = 1;

	zombie->dashSpeed = zombie->speed * 5.5f;
	zombie->originalSpeed = zombie->speed;


	return zombie;
}

Zombie::Zombie(const std::string& name) : SpriteGo(name)
{
}

void Zombie::Dash(bool isDash)
{
	if (isDash)
	{
		speed = dashSpeed;
	}
	else
	{
		speed = originalSpeed;
	}
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

	hasHitBox = true;
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
	attackTimer = attackInterval;

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	uiHud = dynamic_cast<UiHud*>(SCENE_MGR.GetCurrentScene()->FindGo("UI HUD"));
	itemSpawner = dynamic_cast<ItemSpawner*>(SCENE_MGR.GetCurrentScene()->FindGo("Item Spawner"));

	isAlive = true;
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
		return;



	if (!isDash)
	{
		direction = player->GetPosition() - position;
		float distance = Utils::Magnitude(direction);
		Utils::Normalize(direction);
		float angle = Utils::Angle(direction);
		SetRotation(angle);
	}

	sf::Vector2f pos = position + direction * speed * dt;

	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			if (type == Zombie::Types::Bloater)
			{
				player->OnDamage(damage);
				OnDie();
			}
			else
			{
				player->OnDamage(damage);
				attackInterval = 0.f;
			}
		}
	}

	dashTimer += dt;
	if (type == Zombie::Types::Chaser)
	{
		if (!isDash && dashTimer > dashInterval)
		{
			speed = dashSpeed;
			isDash = true;
		}
		if (isDash && dashTimer > dashInterval + dashTime)
		{
			speed = originalSpeed;
			dashTimer = 0.f;
			isDash = false;
		}
	}


}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
	SOUND_MGR.PlaySfx("sound/hit.wav");

	if (!isAlive)
		return;

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Zombie::OnDie()
{
	if (!isAlive)
		return;

	uiHud->SetScore(sceneGame->AddScore(10));
	uiHud->SetZombieCount(sceneGame->MinusZombieNum());
	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);

	SpriteGoEffect* effectBlood = new SpriteGoEffect();
	effectBlood->Init();
	effectBlood->SetOrigin(Origins::MC);
	effectBlood->SetTexture("graphics/blood.png");
	effectBlood->Reset();
	effectBlood->sortLayer = -1;
	effectBlood->sortOrder = 1;
	effectBlood->SetPosition(position);
	effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));

	if (type == Zombie::Types::Bloater)
	{
		effectBlood->SetScale({ 1.7f, 1.7f });
	}

	sceneGame->AddGo(effectBlood);
	SOUND_MGR.PlaySfx("sound/splat.wav");

	int rand = Utils::RandomRange(0,3);  // 0, 1, 2
	if (rand)
	{
		itemSpawner->DropItem(position);
	}
}