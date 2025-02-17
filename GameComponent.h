#pragma once
class Game;

class GameComponent
{
public:

	Game* game;

	GameComponent(Game* game) : game(game) {}

	virtual void DestroyResources() = 0;
	virtual void Draw() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
};

