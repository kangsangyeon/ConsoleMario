#pragma once

#include "ConsoleMario.h"
#include "Object.h"

class PhysicsBody : public Object
{
public:
	PhysicsBody(const Vector2D& _position, Map::TileType _type);

	virtual void UpdateMove(class Map& _map, float _deltaTime, float _gravity);

	virtual void VerticalCollision(class Map& _map, float _deltaTime, float _gravity, float _yVelocity);

	virtual void HorizontalCollision(class Map& _map, float _deltaTime, float _xVelocity);

	void AttemptJump();

public:
	int GetDirectionX() const
	{
		return this->DirectionX;
	}
	void SetDirectionX(int _directionX)
	{
		this->DirectionX = _directionX;
	}
	bool GetWillDestroy() const
	{
		return this->bWillDestroy;
	}

protected:
	virtual void OnCollision(class Map& _map, enum Map::TileType _tileType, Object* _hitObject, Vector2D _hitPoint, Vector2D _velocity);

protected:
	float MoveSpeedPerSecond = 2.0f;
	float JumpForce = 10.0f;

	Vector2D Velocity = Vector2D(0.0f, 0.0f);
	int DirectionX = 0;
	bool bIsGrounded = false;

};

