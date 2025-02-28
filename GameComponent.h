#pragma once
class Game;
#include "directxmath.h"
class GameComponent
{
public:

	Game* game;

	GameComponent(Game* game) : game(game) {}

	virtual void DestroyResources() = 0;
	virtual void Draw() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;

	struct ConstData
	{
		DirectX::XMFLOAT4 radius;
	};

	ConstData data;
};

