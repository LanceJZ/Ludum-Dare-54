#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Initialize(Camera &camera) //Initialize
{
	Cam = camera;

	Man.EM.AddModel3D(ThePlayer = new Player(), &Cam);
	Man.EM.AddCommon(Enemies = new EnemyController());
	Man.EM.AddCommon(Borders = new Border());
	Man.EM.AddCommon(ScoreBoard = new ScoreKeeper());
	ThePlayer->SetManagersRef(Man);
	ThePlayer->SetCameraRef(Cam);
	ThePlayer->SetScoreKeeperRef(ScoreBoard);
	ThePlayer->SetBorderRef(Borders);
	Enemies->SetManagersRef(Man);
	Enemies->SetCameraRef(Cam);
	Enemies->SetPlayerRef(ThePlayer);
	Enemies->SetBorderRef(Borders);
	Enemies->SetScoreKeeperRef(ScoreBoard);
	Borders->SetManagersRef(Man);
	Borders->SetCameraRef(Cam);
	ScoreBoard->SetManagersRef(Man.EM);

	Man.Initialize();

	SetTargetFPS(120);
	SetWindowTitle("Squeeze Play 0.1");

	return true;
}

bool Game::Load()
{
	// Load Models.
	ThePlayer->SetShipModelID(Man.CM.LoadTheModel("PlayerShip"));
	ThePlayer->SetShotModelID(Man.CM.LoadTheModel("PlayerShot"));
	Enemies->SetShipOneModelID(Man.CM.LoadTheModel("EnemyOne"));
	Enemies->SetShipTwoModelID(Man.CM.LoadTheModel("EnemyTwo"));
	Enemies->SetShotModelID(Man.CM.LoadTheModel("EnemyShot"));
	Borders->SetBorderModelID(Man.CM.LoadTheModel("Border"));

	// Load Sounds.
	ThePlayer->SetSounds(Man.CM.LoadAndGetSound("PlayerFire"),
		Man.CM.LoadAndGetSound("PlayerExplode"),
		Man.CM.LoadAndGetSound("PlayerThrust"));

	ThePlayer->SetShotSound(Man.CM.LoadAndGetSound("BorderHit"));

	Enemies->SetSounds(Man.CM.LoadAndGetSound("EnemyOneHit"),
		Man.CM.LoadAndGetSound("EnemyTwoHit"),
		Man.CM.LoadAndGetSound("EnemyOneFire"));

	return true;
}

bool Game::BeginRun()
{
	Man.BeginRun(); //Any Entities added after this point need this method fired manually.

	NewGame();

	return true;
}

void Game::ProcessInput()
{
	Man.EM.Input();

	if (State == MainMenu)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 15))//Start button
			{
				NewGame();
			}
		}

		if (IsKeyPressed(KEY_N))
		{
			NewGame();
		}

		if (IsKeyPressed(KEY_D))
		{

		}
	}

	if (State == InPlay)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				State = Pause;
			}

			if (IsGamepadButtonPressed(0, 8)) //X button
			{
				PlayBackgroundMusic = !PlayBackgroundMusic;
			}
		}

		if (IsKeyPressed(KEY_M))
		{
			PlayBackgroundMusic = !PlayBackgroundMusic;
		}


		if (IsKeyPressed(KEY_P))
		{
			State = Pause;
		}
	}
	else if (State == Pause)
	{
		if (IsKeyPressed(KEY_P))
		{
			State = InPlay;
		}

		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				State = InPlay;
			}
		}
	}
}


void Game::Update(float deltaTime)
{
	if (State == Pause)
		return;

	if (ThePlayer->BeenHit)
	{
		if (ThePlayer->GameOver)
		{
			NewGame();
			return;
		}

		ThePlayer->Reset();
		Enemies->Reset();
		Borders->Reset();
		ThePlayer->BeenHit = false;

	}

	Man.EM.Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(Cam);

	//3D Drawing here.
	Draw3D();

	EndMode3D();

	//2D drawing, fonts go here.

	Draw2D();
#ifdef _DEBUG
	DrawFPS(5, 5);
#endif

	EndDrawing();
}

void Game::NewGame()
{
	State = InPlay;

	ThePlayer->BeenHit = false;
	ThePlayer->NewGame();
	Enemies->Reset();
	Borders->Reset();
	ScoreBoard->Reset();
}

void Game::Draw3D()
{
	Man.EM.Draw3D();
}

void Game::Draw2D()
{
	Man.EM.Draw2D();
}
