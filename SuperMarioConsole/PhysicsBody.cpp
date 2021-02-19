#include "PhysicsBody.h"

#include <iostream>
#include "GameInstance.h"
#include "Map.h"

PhysicsBody::PhysicsBody(const Vector2D& _position, Map::TileType _type) : Object(_position, _type)
{
}

void PhysicsBody::UpdateMove(Map& _map, float _deltaTime, float _gravity)
{
	VerticalCollision(_map, _deltaTime, _gravity, _deltaTime * _gravity);

	HorizontalCollision(_map, _deltaTime, DirectionX * MoveSpeedPerSecond);

	// TODO DEBUG
	if (GetType() == Map::TileType::Player)
	{
		std::cout << "player: " << GetPosition().ToString() << std::endl;
	}
	else
	{
		std::cout << StringFormat("enemy(%x): ", this) << GetPosition().ToString() << std::endl;
	}
}

void PhysicsBody::VerticalCollision(Map& _map, float _deltaTime, float _gravity, float _yVelocity)
{
	Velocity.Y += _yVelocity;

	Vector2D _newPosition = Vector2D(Position.X, Position.Y + Velocity.Y * _deltaTime);

	Map::TileType _currentTile;
	Object* _hitObject;
	bool bCanGo = _map.CheckCollision(this, _newPosition, _currentTile, _hitObject) == false;

	OnCollision(_map, _currentTile, _hitObject, _newPosition, Velocity);

	if (bCanGo)
	{
		Position = _newPosition;
		bIsGrounded = false;
	}
	else
	{
		Velocity.Y = 0.0f;
		bIsGrounded = true;
	}
}

void PhysicsBody::HorizontalCollision(Map& _map, float _deltaTime, float _xVelocity)
{
	Velocity.X = _xVelocity;
	Vector2D _newPosition = Vector2D(Position.X + Velocity.X * _deltaTime, Position.Y);

	Map::TileType _currentTile;
	Object* _hitObject;
	bool bCanGo = _map.CheckCollision(this, _newPosition, _currentTile, _hitObject) == false;

	OnCollision(_map, _currentTile, _hitObject, _newPosition, Velocity);

	if (bCanGo)
	{
		Position = _newPosition;
	}
}

void PhysicsBody::OnCollision(Map& map, Map::TileType _tileType, Object* _hitObject, Vector2D _hitPoint, Vector2D _velocity)
{

}

void PhysicsBody::AttemptJump()
{
	if (this->bIsGrounded == false)
		return;

	this->Velocity.Y = JumpForce;
	this->bIsGrounded = false;

}
