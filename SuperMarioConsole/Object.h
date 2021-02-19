#pragma once

#include "Map.h"
#include "Vector2D.h"

class Object
{
public:
	Object(const Vector2D& _position, Map::TileType _type);

	virtual ~Object() = default;

public:
	virtual void Destroy();


public:
	Vector2D GetPosition() const;

	void SetPosition(Vector2D _position);

	Map::TileType GetType() const;

	bool GetWillDestroy() const;


protected:
	Vector2D Position = Vector2D();
	Map::TileType Type = Map::TileType::Undefinded;

	bool bWillDestroy = false;

};
