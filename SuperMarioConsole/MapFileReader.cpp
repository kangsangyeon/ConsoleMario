#include "MapFileReader.h"

#include <fstream>
#include <algorithm>
#include <string>
#include "Map.h"
#include "Vector2D.h"
#include "Player.h"
#include "Enemy.h"
#include "StaticObject.h"
#include "WarpZone.h"
#include "GoalZone.h"

bool MapFileReader::
ReadFromFile(std::string _fileNameBase, int _entry, class Map** _outMap, class Player** _outPlayer, std::vector<PhysicsBody*>** _outPhysicsBodies, std::vector<StaticObject*>** _outStaticObjects)
{
	const std::string _fileName = InRange(_entry, 1, 9) == false ? _fileNameBase : _fileNameBase + StringFormat("_%d", _entry);
	std::ifstream _ifstream{ _fileName + ".txt" };

	if (_ifstream.is_open() == false)
		return false;

	std::vector<std::vector<Map::TileType>> _mapData;
	int _mapXCount = INT_MAX;
	int _mapYCount = 0;

	std::vector<PhysicsBody*>* _physicsBodies = new std::vector<PhysicsBody*>();

	std::vector<StaticObject*>* _staticObjects = new std::vector<StaticObject*>();

	Player* _player = new Player(Vector2D(0, 0));
	_physicsBodies->push_back(_player);

	while (true)
	{
		std::string _inputLine;
		std::getline(_ifstream, _inputLine);

		if (_inputLine.empty())
			break;

		_mapXCount = _inputLine.size() < _mapXCount ? _inputLine.size() : _mapXCount;
		_mapYCount++;

		_mapData.push_back(std::vector<Map::TileType>());
		for (int _i = 0; _i < _inputLine.size(); _i++)
		{
			const auto& _c = _inputLine[_i];
			auto _currentTile = static_cast<Map::TileType>(_c);

			if (_currentTile == Map::TileType::StartPoint)
			{
				_player->SetPosition(Vector2D(_i, _mapYCount - 1));

				_mapData[_mapYCount - 1].push_back(Map::TileType::Empty);
			}
			else if (_currentTile == Map::TileType::Enemy)
			{
				Enemy* _enemy = new Enemy(Vector2D(_i, _mapYCount - 1));

				_physicsBodies->push_back(_enemy);

				_mapData[_mapYCount - 1].push_back(Map::TileType::Empty);
			}
			else if (_currentTile == Map::TileType::GoalZone)
			{
				GoalZone* _goalZone = new GoalZone(Vector2D(_i, _mapYCount - 1));

				_staticObjects->push_back(_goalZone);

				_mapData[_mapYCount - 1].push_back(Map::TileType::Empty);
			}
			else if (InRange<char>(_c, '1', '9'))
			{
				WarpZone* _warpZone = new WarpZone(Vector2D(_i, _mapYCount - 1), static_cast<int>(_c - '0'));

				_staticObjects->push_back(_warpZone);

				_mapData[_mapYCount - 1].push_back(Map::TileType::Empty);
			}
			else
			{
				_mapData[_mapYCount - 1].push_back(_currentTile);
			}

		}

	}

	// 플레이어가 놓이길 원하는 위치(entry)값을 전달받은 경우 그 곳으로 이동시킨다.
	if (InRange(_entry, 1, 9))
	{
		for (int _i = 0; _i < _staticObjects->size(); _i++)
		{
			WarpZone* _warpZone = dynamic_cast<WarpZone*>(_staticObjects->at(_i));
			if (_warpZone != nullptr && _warpZone->GetEntry() == _entry)
			{
				_player->SetPosition(_warpZone->GetPosition());
				break;
			}
		}
	}

	// 맵의 행을 읽은 순서의 역순으로 정렬한다.
	// 맵을 하늘부터 땅 순으로 읽었기 때문이다.
	// 인덱스 0을 땅쪽으로 하기 위해서 역순으로 정렬해야 한다.
	std::reverse(std::begin(_mapData), std::end(_mapData));

	// PhysicsBody와 StaticObject 역시 Y축 위치를 거꾸로 교정한다.
	for (auto _body : *_physicsBodies)
	{
		_body->SetPosition(
			Vector2D(_body->GetPosition().X,
				_mapYCount - _body->GetPosition().Y - 1)
		);

	}

	for (auto _object : *_staticObjects)
	{
		_object->SetPosition(
			Vector2D(_object->GetPosition().X,
				_mapYCount - _object->GetPosition().Y - 1)
		);

	}

	*_outMap = new Map(_mapData, _physicsBodies, _staticObjects, _mapXCount, _mapYCount);

	*_outPlayer = _player;

	*_outPhysicsBodies = _physicsBodies;

	*_outStaticObjects = _staticObjects;


	return true;
}