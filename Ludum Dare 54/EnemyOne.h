#pragma once
#include "Model3D.h"
#include "EntityManager.h"
#include "Player.h"
#include "Border.h"

class EnemyOne : public Model3D
{
public:
	EnemyOne();
	virtual ~EnemyOne();

	void SetManagersRef(EntityManager& man);
	void SetPlayerRef(Player* player);
	void SetBorderRef(Border* borders);

	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

	void Spawn();

private:
	float Speed = 33.666f;
	float MaxSpeed = 33.666;
	float TurnSpeed = 0.25f;
	float MaxTurnSpeed = 0.25f;
	float RotateMagnitude = PI / 2;

	EntityManager* Man = {};
	Player* ThePlayer = {};
	Border* Borders = {};

	void ChasePlayer();
	bool CheckCollision();
	void Collide();
};
