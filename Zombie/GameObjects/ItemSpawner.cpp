#include "pch.h"
#include "ItemSpawner.h"

ItemSpawner::ItemSpawner(const std::string& name) : Spawner(name)
{
}

GameObject* ItemSpawner::Create()
{
	Item::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size())];

	int value = 0;
	switch (itemType)
	{
	case Item::Types::Ammo:
		value = ammoItemValue;
		break;
	case Item::Types::Health:
		value = hpItemValue;
		break;
	}

	return Item::Create(itemType, value);
}

void ItemSpawner::DropItem(const sf::Vector2f& position)
{
	GameObject* drop = Create();
	drop->Init();
	drop->Reset();
	drop->SetOrigin(Origins::MC);
	drop->SetPosition(position);

	itemTypes.push_back(Item::Types::Health); 

	SCENE_MGR.GetCurrentScene()->AddGo(drop);
}

void ItemSpawner::Reset()
{
	Spawner::Reset();

	itemTypes.clear();
	itemTypes.push_back(Item::Types::Ammo);


	interval = 3.f;
	spawnCount = 1;
	radius = 250.f;
	timer = 0.f;
}