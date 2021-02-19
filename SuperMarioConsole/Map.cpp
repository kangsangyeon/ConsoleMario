#include "Map.h"

#include <iostream>

#include "PhysicsBody.h"
#include "StaticObject.h"

Map::Map(std::vector<std::vector<TileType>> _data, std::vector<class PhysicsBody*>* _physicsBodies, std::vector<class StaticObject*>* _staticObjects, int _xCount, int _yCount) : Data(_data), PhysicsBodies(_physicsBodies), StaticObjects(_staticObjects), XCount(_xCount), YCount(_yCount)
{
}

bool Map::InMapRange(Vector2D _position) const
{
	if (InRange(_position.X, 0.0f, static_cast<float>(XCount - 1)) == false
		|| InRange(_position.Y, 0.0f, static_cast<float>(YCount - 1)) == false)
		return false;
	else
		return true;
}

/// <summary>
/// 맵 상에서 주어진 위치가 갈 수 있는 곳인지를 확인하고, 그 이동 가능 여부와 타일 타입을 반환합니다.
/// </summary>
bool Map::CheckCollision(PhysicsBody* _me, Vector2D _position, TileType& _outTileType, Object*& _outObject) const
{
	_outObject = nullptr;

	bool _isInMapRange = InMapRange(_position) == true;
	TileType _currentTile = _isInMapRange ? GetData()[_position.GetRoundedY()][_position.GetRoundedX()]
		: TileType::OutOfBounds;

	std::vector<Object*> _allObjects = std::vector<Object*>();
	if (StaticObjects != nullptr)
		_allObjects.insert(_allObjects.end(), StaticObjects->begin(), StaticObjects->end());
	if (PhysicsBodies != nullptr)
		_allObjects.insert(_allObjects.end(), PhysicsBodies->begin(), PhysicsBodies->end());

	for (auto _body : _allObjects)
	{
		if (_me == _body)
			continue;

		if (_body->GetPosition().GetRounded() == _position.GetRounded())
		{
			_currentTile = _body->GetType();
			_outObject = _body;
			break;
		}
	}

	_outTileType = _currentTile;

	switch (_currentTile)
	{
	case TileType::Undefinded:
	case TileType::OutOfBounds:
	case TileType::Block:
	case TileType::Tower:
		return true;
	}

	return false;

}


Map::TileType Map::GetTile(Vector2D _position) const
{
	if (InMapRange(_position) == false)
		return TileType::OutOfBounds;

	return Data[_position.Y][_position.X];
}

void Map::SetTile(Vector2D _position, TileType _tile)
{
	if (InMapRange(_position) == false)
		return;

	Data[_position.Y][_position.X] = _tile;
}
