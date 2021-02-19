#include "ConsoleRenderer.h"

#include <iostream>
#include <sstream>
#include <string>

#include "GameInstance.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "StaticObject.h"

void ConsoleRenderer::Render(Map* _map, Vector2D _centerPosition)
{
	auto _renderData = _map->GetData();

	for (const auto& _object : *_map->GetStaticObjects())
	{
		Vector2D _position = _object->GetPosition();

		if (_map->InMapRange(_position))
			_renderData[_position.GetRoundedY()][_position.GetRoundedX()] = _object->GetType();
	}

	for (const auto& _body : *_map->GetPhysicsBodies())
	{
		Vector2D _position = _body->GetPosition();

		if (_map->InMapRange(_position))
			_renderData[_position.GetRoundedY()][_position.GetRoundedX()] = _body->GetType();
	}

	const int _mapXCount = _map->GetMapXCount();
	const int _mapYCount = _map->GetMapYCount();

	const int _xRangeStart = GameInstance::ScreenXCount / 2 > _centerPosition.X
		? 0
		: _centerPosition.X - (GameInstance::ScreenXCount / 2);
	const int _xRangeEnd = _xRangeStart + GameInstance::ScreenXCount < _mapXCount
		? _xRangeStart + GameInstance::ScreenXCount
		: _mapXCount - 1;

	std::stringbuf _buffer;
	std::ostream _os(&_buffer);

	for (int _y = _mapYCount - 1; _y >= 0; _y--)
	{
		for (int _x = _xRangeStart; _x <= _xRangeEnd; _x++)
		{
			Map::TileType _tile = _renderData[_y][_x];

			switch (_tile)
			{
			case Map::TileType::Undefinded:
				break;
			case Map::TileType::Empty:
				_os << "  ";
				break;
			case Map::TileType::Block:
				_os << "##";
				break;
			case Map::TileType::Tower:
				_os << "00";
				break;
			case Map::TileType::WarpZone:
				_os << "WW";
				break;
			case Map::TileType::Coin:
				_os << "CC";
				break;
			case Map::TileType::Player:
				_os << "PP";
				break;
			case Map::TileType::Enemy:
				_os << "MM";
				break;
			case Map::TileType::GoalZone:
				_os << "GG";
				break;
			}

		}

		_os << std::endl;
	}

	std::cout << _buffer.str();
}
