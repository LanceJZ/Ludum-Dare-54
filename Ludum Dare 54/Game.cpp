#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Initialize(Camera &camera) //Initialize
{
	TheCamera = camera;

	Man.Initialize();
	Man.EM.AddModel3D(ThePlayer = new Player(), &TheCamera);
	ThePlayer->Initialize();
	ThePlayer->SetManagersRef(Man);

	SetTargetFPS(120);
	SetWindowTitle("Ludum Dare 54");

	return true;
}

bool Game::Load()
{
	ThePlayer->SetShipModelID(Man.CM.LoadTheModel("PlayerShip"));

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

	Man.EM.Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(TheCamera);

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

}

void Game::Draw3D()
{
	Man.EM.Draw3D();
}

void Game::Draw2D()
{
}