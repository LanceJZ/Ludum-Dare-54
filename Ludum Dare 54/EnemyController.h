#pragma once
#include "Common.h"
#include "EnemyOne.h"
#include "Managers.h"

class EnemyController : public Common
{
public:
	EnemyController();
	virtual ~EnemyController();

	std::vector<EnemyOne*> Ones;

	void SetManagersRef(Managers& man);
	void SetCameraRef(Camera& cam);
	void SetPlayerRef(Player* player);
	void SetShipOne(size_t modelID);

	bool Initialize();
	bool BeginRun();

	void Update();
	void Draw();

private:
	size_t ShipOneModelID = 0;
	size_t SpawnTimerID = 0;
	Managers* Man = {};
	Camera* Cam = {};
	Player* ThePlayer = {};

	void SpawnOne(size_t count);
};

