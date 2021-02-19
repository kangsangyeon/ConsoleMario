#include "Enemy.h"

Enemy::Enemy(Vector2D _position) : PhysicsBody(_position, Map::TileType::Enemy)
{
	DirectionX = -1;
}

void Enemy::OnCollision(Map& _map, Map::TileType _tileType, Object* _hitObject, Vector2D _hitPoint, Vector2D _velocity)
{
	if (GetWillDestroy())
		return;

	if (_tileType == Map::TileType::Tower
		|| _tileType == Map::TileType::Enemy)
	{
		DirectionX = DirectionX * -1;
	}
	else if (_tileType == Map::TileType::OutOfBounds)
	{
		Destroy();
	}
	else if (_tileType == Map::TileType::Player)
	{
		_hitObject->Destroy();
	}
}