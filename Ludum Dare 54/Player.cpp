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

void Player::SetCameraRef(Camera& cam)
{
	Cam = &cam;
}

void Player::SetShipModelID(size_t modelID)
{
	ShipModelID = modelID;
}

void Player::SetShotModelID(size_t modelID)
{
	ShotModelID = modelID;
}

bool Player::Initialize()
{
	Model3D::Initialize();
	Cull = false;
	Radius = 20;
	Enabled = true;
	return false;
}

bool Player::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

	SetModel(Man->CM.GetModel(ShipModelID), 15.0f);

	return false;
}

void Player::Input()
{
	Model3D::Input();

	Keyboard();

	if (IsGamepadAvailable(0))
	{
		GamePad();
	}
}

void Player::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (!ThrustIsOn)
	{
		ThrustOff(deltaTime);
	}
	else if (ThrustIsOn && Enabled)
	{
		ThrustOn(deltaTime);
	}

	CheckScreenEdge();
}

void Player::Draw()
{
	Model3D::Draw();

}

bool Player::GetShieldIsOn()
{
	// Shield->Enabled;

	return false;
}

bool Player::GetShieldIsOff()
{
	//StopSound(Sound06);

	//Shield->Enabled = false;

	return true;
}

void Player::Fire()
{
	bool spawnNewShot = true;
	size_t shotNumber = Shots.size();

	for (size_t shotCheck = 0; shotCheck < shotNumber; shotCheck++)
	{
		if (!Shots[shotCheck]->Enabled)
		{
			spawnNewShot = false;
			shotNumber = shotCheck;
			break;
		}
	}

	if (spawnNewShot)
	{
		Shots.push_back(new PlayerShot());
		Man->EM.AddModel3D(Shots[shotNumber]);
		Shots[shotNumber]->SetModel(Man->CM.GetModel(ShotModelID), 20.0f);
		Shots[shotNumber]->SetManagersRef(Man->EM);
		Shots[shotNumber]->BeginRun(Cam);
	}

	float speed = 400.0f;
	float timer = 1.0f;
	Shots[shotNumber]->Spawn(Position, Rotation, VelocityFromAngleZ(speed), timer);
}

void Player::ShieldOn()
{
}

void Player::ShieldOff()
{
}

void Player::ThrustOn(float deltaTime)
{
	Acceleration = AccelerationToMaxAtRotation(350.666f, 0.001f, deltaTime);
}

void Player::ThrustOff(float deltaTime)
{
	Acceleration = DecelerationToZero(1.25f, deltaTime);
}

void Player::GamePad()
{
	//Button B is 6 for Shield //Button A is 7 for Fire //Button Y is 8 for Hyperspace
	//Button X is 5	//Left bumper is 9 //Right bumper is 11 for Shield //Left Trigger is 10
	//Right Trigger is 12 for Thrust //Dpad Up is 1 for	//Dpad Down is 3 for
	//Dpad Left is 4 for rotate left //Dpad Right is 2 for rotate right
	//Axis 1 is -1 for , 1 for  on left stick.
	//Axis 0 is -1 for Left, 1 for right on left stick.

	if (IsGamepadButtonDown(0, 12))
	{
		ThrustIsOn = true;
	}
	else
	{
		ThrustIsOn = false;
	}

	float velocityRotZ = 0.07666f;

	if (IsGamepadButtonDown(0, 4) || GetGamepadAxisMovement(0, 0) < -0.25f)
	{
		Rotation -= velocityRotZ;
	}
	else if (IsGamepadButtonDown(0, 2) || GetGamepadAxisMovement(0, 0) > 0.25f)
	{
		Rotation += velocityRotZ;
	}

	if (IsGamepadButtonPressed(0, 7))
	{
		Fire();
	}

	if (IsGamepadButtonDown(0, 11) || IsGamepadButtonDown(0, 6))
	{
		ShieldOn();
	}
	else
	{
		ShieldOff();
	}
}

void Player::Keyboard()
{
	float velocityRotZ = 3.666f;

	if (IsKeyDown(KEY_RIGHT))
	{
		RotationVelocity = velocityRotZ;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		RotationVelocity = -velocityRotZ;
	}
	else
	{
		RotationVelocity = 0;
	}

	if (IsKeyDown(KEY_UP))
	{
		ThrustIsOn = true;
	}
	else
	{
		ThrustIsOn = false;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) ||
		IsKeyPressed(KEY_SPACE))
	{
		Fire();
	}

	if (IsKeyDown(KEY_DOWN))
	{
		ShieldOn();
	}
	else
	{
		ShieldOff();
	}
}