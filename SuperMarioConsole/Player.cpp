#include "Player.h"

#include <iostream>

#include "GameInstance.h"
#include "WarpZone.h"

Player::Player(Vector2D _position) : PhysicsBody(_position, Map::TileType::Player)
{
	MoveSpeedPerSecond = 5.0f;
}

void Player::BindPlayerInput(PlayerInput* _input)
{
	this->Input = _input;
}

void Player::UpdateMove(Map& _map, float _deltaTime, float _gravity)
{
	SetDirectionX(Input->GetHorizontal());

	if (Input->GetJump())
		AttemptJump();

	PhysicsBody::UpdateMove(_map, _deltaTime, _gravity);
}

void Player::OnCollision(Map& _map, Map::TileType _tileType, Object* _hitObject, Vector2D _hitPoint, Vector2D _velocity)
{
	if (_tileType == Map::TileType::Enemy)
	{
		if (_velocity.Y < 0)
			_hitObject->Destroy();
		else
			Destroy();
	}
	else if (_tileType == Map::TileType::Coin)
	{
		GameInstance::GetInstance()->AddGameScore();
		_map.SetTile(_hitPoint.GetRounded(), Map::TileType::Empty);
	}
	else if (_tileType == Map::TileType::WarpZone)
	{
		auto _warpZone = dynamic_cast<WarpZone*>(_hitObject);
		if (_warpZone != nullptr
			&& Input->GetDown())
		{
			GameInstance::GetInstance()->ReserveStartLevel(GameInstance::GetInstance()->MapFileName, _warpZone->GetEntry());
		}
	}
	else if (_tileType == Map::TileType::GoalZone)
	{
		bIsClear = true;
	}

}

void Player::Destroy()
{
	PhysicsBody::Destroy();

	bIsDead = true;
}

bool Player::GetIsDead() const
{
	return this->bIsDead;
}

bool Player::GetIsClear() const
{
	return this->bIsClear;
}
