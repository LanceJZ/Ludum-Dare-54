#pragma once
#include <memory>
#include "raylib.h"
#include "Managers.h"
#include "Player.h"
#include "EnemyController.h"

enum GameState
{
	PlayerHit,
	Over,
	InPlay,
	Pause,
	HighScores,
	MainMenu
};


class Game
{
public:
	Game();
	virtual ~Game();

	bool PlayBackgroundMusic = true;
	GameState State = MainMenu;
	Camera Cam = { 0 };

	bool Initialize(Camera &camera);
	bool Load();
	bool BeginRun();
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

private:
	Managers Man = {};
	Player* ThePlayer = {};
	EnemyController* Enemies = {};

	void NewGame();
	void Draw3D();
	void Draw2D();
};

