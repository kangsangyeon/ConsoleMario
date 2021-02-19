#pragma once

#include "ConsoleMario.h"
#include <string>
#include <vector>

#include "Vector2D.h"

class Map
{
public:
	enum class TileType : char
	{
		Undefinded = (char)-1, OutOfBounds = (char)-9,
		Empty = '.', Block = '#', Tower = '0', Coin = 'C', WarpZone, GoalZone = 'G',
		StartPoint = 'S', Player = 'P', Enemy = 'E'
	};

	Map() = default;
	Map(std::vector<std::vector<TileType>> _data, std::vector<class PhysicsBody*>* _physicsBodies, std::vector<class StaticObject*>* _staticObjects, int _xCount, int _yCount);

	bool InMapRange(Vector2D _position) const;

	bool CheckCollision(PhysicsBody* _me, Vector2D _position, TileType& _outTileType, class Object*& _outObject) const;

public:
	TileType GetTile(Vector2D _position) const;

	void SetTile(Vector2D _position, TileType _tile);

	std::vector<std::vector<TileType>> GetData() const
	{
		return this->Data;
	}

	std::vector<class PhysicsBody*>* GetPhysicsBodies() const
	{
		return this->PhysicsBodies;
	}

	std::vector<class StaticObject*>* GetStaticObjects() const
	{
		return this->StaticObjects;
	}

	int GetMapXCount() const
	{
		return this->XCount;
	}

	int GetMapYCount() const
	{
		return this->YCount;
	}

private:
	std::vector<std::vector<TileType>> Data;
	std::vector<class PhysicsBody*>* PhysicsBodies;
	std::vector<class StaticObject*>* StaticObjects;
	int XCount;
	int YCount;

};