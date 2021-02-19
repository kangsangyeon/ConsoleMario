#pragma once

#include "ConsoleMario.h"
#include "PhysicsBody.h"

class Enemy : public PhysicsBody
{
public:
	Enemy(Vector2D _position);

protected:
	void OnCollision(Map& _map, Map::TileType _tileType, Object* _hitObject, Vector2D _hitPoint,
		Vector2D _velocity) override;

};
