#pragma once
#include "Common.h"
#include "EnemyOne.h"
#include "EnemyTwo.h"
#include "Managers.h"
#include "Border.h"

class EnemyController : public Common
{
public:
	EnemyController();
	virtual ~EnemyController();

	std::vector<EnemyOne*> Ones;
	std::vector<EnemyTwo*> Twos;

	void SetManagersRef(Managers& man);
	void SetCameraRef(Camera& cam);
	void SetPlayerRef(Player* player);
	void SetBorderRef(Border* borders);
	void SetShipOneModelID(size_t modelID);
	void SetShipTwoModelID(size_t modelID);
	void SetShotModelID(size_t modelID);

	bool Initialize();
	bool BeginRun();

	void Update();
	void Draw();

private:
	size_t ShipOneModelID = 0;
	size_t ShipTwoModelID = 0;
	size_t ShotModelID = 0;
	size_t SpawnTimerID = 0;
	int WaveOne = 0;

	Managers* Man = {};
	Camera* Cam = {};
	Player* ThePlayer = {};
	Border* Borders = {};

	void SpawnOne(size_t count);
	void SpawnTwo(size_t count);
};

