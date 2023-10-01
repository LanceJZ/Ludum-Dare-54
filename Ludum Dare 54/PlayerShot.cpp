#include "PlayerShot.h"

PlayerShot::PlayerShot()
{
}

PlayerShot::~PlayerShot()
{
}

void PlayerShot::SetManagersRef(EntityManager& man)
{
	Man = &man;
}

bool PlayerShot::Initialize()
{
	Model3D::Initialize();
	Cull = false;

	return false;
}

bool PlayerShot::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	ShotTimerID = Man->AddTimer();

	return true;
}

void PlayerShot::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (Man->Timers[ShotTimerID]->Elapsed())
	{
		Enabled = false;
	}
}

void PlayerShot::Draw()
{
	Model3D::Draw();

}

void PlayerShot::Spawn(Vector3 pos, float rot, Vector3 vel, size_t timerAmount)
{
	Position = pos;
	Position.z = 10;
	Velocity = vel;
	Rotation = rot;
	Enabled = true;

	Man->Timers[ShotTimerID]->Reset(timerAmount);
}
