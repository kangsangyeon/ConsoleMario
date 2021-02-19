#include "Object.h"


Object::Object(const Vector2D& _position, Map::TileType _type) : Position(_position), Type(_type)
{
}

void Object::Destroy()
{
	this->bWillDestroy = true;
}

Vector2D Object::GetPosition() const
{
	return this->Position;
}

void Object::SetPosition(Vector2D _position)
{
	this->Position = _position;
}

Map::TileType Object::GetType() const
{
	return this->Type;
}

bool Object::GetWillDestroy() const
{
	return this->bWillDestroy;
}

