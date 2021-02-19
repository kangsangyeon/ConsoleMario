#include "WarpZone.h"

WarpZone::WarpZone(const Vector2D& _position, int _entry) : StaticObject(_position, Map::TileType::WarpZone)
{
	this->Entry = _entry;
}

int WarpZone::GetEntry() const
{
	return this->Entry;
}
