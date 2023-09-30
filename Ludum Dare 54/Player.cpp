#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetManagersRef(Managers& man)
{
	Man = &man;
}

void Player::SetShipModelID(size_t modelID)
{
	ShipModelID = modelID;
	SetModel(Man->CM.GetModel(modelID), 15.0f);
}

bool Player::Initialize()
{
	Enabled = true;
	return false;
}

bool Player::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	return false;
}

void Player::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Player::Draw()
{
	Model3D::Draw();

}
