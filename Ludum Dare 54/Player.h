#pragma once
#include "Managers.h"
#include "Common.h"
//#include "PlayerShot"

class Player : public Model3D
{
public:
	Player();
	virtual ~Player();

	void SetManagersRef(Managers& man);
	void SetShipModelID(size_t modelID);
	void SetShotModelID(size_t modelID);
	bool Initialize();
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

private:
	size_t ShipModelID = 0;
	Managers* Man = {};

};
