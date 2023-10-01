#include "EnemyOne.h"

EnemyOne::EnemyOne()
{
}

EnemyOne::~EnemyOne()
{
}

void EnemyOne::SetManagersRef(EntityManager& man)
{
	Man = &man;
}

void EnemyOne::SetPlayerRef(Player* player)
{
	ThePlayer = player;
}

bool EnemyOne::Initialize()
{
	Model3D::Initialize();

	//Scale = 1.0f;
	Radius = 15;

	return false;
}

bool EnemyOne::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	return false;
}

void EnemyOne::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	ChasePlayer();

	if (CheckCollision()) Collide();
}

void EnemyOne::Draw()
{
	Model3D::Draw();

}

void EnemyOne::Spawn()
{
	Enabled = true;
	float buffer = 20.0f;
	float x = GetRandomFloat(-WindowWidth, WindowWidth);
	float y = GetRandomFloat(-WindowHeight, WindowHeight);

	if (GetRandomValue(1, 10) < 5)
	{
		if (GetRandomValue(1, 10) < 5)
		{
			x = WindowWidth + buffer;
		}
		else
		{
			x = -WindowWidth - buffer;
		}
	}
	else
	{
		if (GetRandomValue(1, 10) < 5)
		{
			y = WindowHeight + buffer;
		}
		else
		{
			y = WindowHeight - buffer;
		}
	}

	X(x);
	Y(y);

	Speed = GetRandomFloat(MaxSpeed * 0.5f, MaxSpeed);
	TurnSpeed = GetRandomFloat(MaxTurnSpeed * 0.5f, MaxTurnSpeed);

	Rotation = AngleFromVectorZ(ThePlayer->Position);
}

void EnemyOne::ChasePlayer()
{
	RotateVelocity(ThePlayer->Position, TurnSpeed, Speed);
}

bool EnemyOne::CheckCollision()
{
	if (CirclesIntersect(*ThePlayer))
	{
		return true;
	}

	for (auto &shot : ThePlayer->Shots)
	{
		if (CirclesIntersect(*shot) && shot->Enabled)
		{
			shot->Enabled = false;
			return true;
		}
	}

	return false;
}

void EnemyOne::Collide()
{
	Enabled = false;
	X(WindowWidth + 50);
}