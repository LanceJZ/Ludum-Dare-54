#pragma once
#include "Model3D.h"
#include "Managers.h"
#include "Player.h"
#include "Border.h"
#include "EnemyShot.h"

class EnemyTwo : public Model3D
{
public:
	EnemyTwo();
	virtual ~EnemyTwo();

	std::vector<EnemyShot*> Shots;

	void SetManagersRef(Managers& man);
	void SetPlayerRef(Player* player);
	void SetBorderRef(Border* borders);
	void SetShotModelID(size_t modelID);

	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn();

private:
	size_t DistanceTimerID = 0;
	size_t FireTimerID = 0;
	size_t ShotModelID = 0;
	float Speed = 22.666f;
	float MaxSpeed = 52.666;

	Managers* Man = {};
	Player* ThePlayer = {};
	Border* Borders = {};

	void ChasePlayer();
	bool CheckCollision();
	void Collide();
	void Fire();
};