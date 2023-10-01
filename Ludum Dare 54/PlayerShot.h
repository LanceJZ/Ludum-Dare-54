#pragma once
#include "Managers.h"
#include "Model3D.h"

class PlayerShot : public Model3D
{
public:
	PlayerShot();
	virtual ~PlayerShot();

	void SetManagersRef(EntityManager& man);
	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 pos, float rot, Vector3 vel, size_t timerAmount);

private:
	size_t ShotTimerID = 0;
	EntityManager* Man = {};
};
