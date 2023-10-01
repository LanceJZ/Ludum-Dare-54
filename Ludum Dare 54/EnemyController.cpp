#include "EnemyController.h"

EnemyController::EnemyController()
{

}

EnemyController::~EnemyController()
{
}

void EnemyController::SetManagersRef(Managers& man)
{
	Man = &man;
}

void EnemyController::SetCameraRef(Camera& cam)
{
	Cam = &cam;
}

void EnemyController::SetPlayerRef(Player* player)
{
	ThePlayer = player;
}

void EnemyController::SetBorderRef(Border* borders)
{
	Borders = borders;
}

void EnemyController::SetShipOneModelID(size_t modelID)
{
	ShipOneModelID = modelID;
}

bool EnemyController::Initialize()
{

	return false;
}

bool EnemyController::BeginRun()
{
	SpawnTimerID = Man->EM.AddTimer(3.0f);

	return false;
}

void EnemyController::Update()
{
	if (Man->EM.Timers[SpawnTimerID]->Elapsed())
	{
		Man->EM.Timers[SpawnTimerID]->Reset();
		SpawnOne(5);
	}
}

void EnemyController::Draw()
{

}

void EnemyController::SpawnOne(size_t count)
{
	for (int one = 0; one < count; one++)
	{
		bool spawnNewOne = true;
		size_t oneNumber = Ones.size();

		for (size_t oneCheck = 0; oneCheck < oneNumber; oneCheck++)
		{
			if (!Ones[oneCheck]->Enabled)
			{
				spawnNewOne = false;
				oneNumber = oneCheck;
				break;
			}
		}

		if (spawnNewOne)
		{
			Ones.push_back(new EnemyOne());
			Man->EM.AddModel3D(Ones[oneNumber]);
			Ones[oneNumber]->SetModel(Man->CM.GetModel(ShipOneModelID), 15.0f);
			Ones[oneNumber]->SetManagersRef(Man->EM);
			Ones[oneNumber]->SetPlayerRef(ThePlayer);
			Ones[oneNumber]->SetBorderRef(Borders);
			Ones[oneNumber]->BeginRun(Cam);
		}

		Ones[oneNumber]->Spawn();
	}
}
