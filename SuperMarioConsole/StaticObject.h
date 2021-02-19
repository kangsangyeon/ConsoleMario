#pragma once

#include "Object.h"

class StaticObject : public Object
{
public:
	StaticObject(const Vector2D& _position, Map::TileType _type);

	~StaticObject() override = default;

};
