#pragma once

#include "StaticObject.h"

class WarpZone : public StaticObject
{
public:
	WarpZone(const Vector2D& _position, int _entry);

	~WarpZone() override = default;

public:
	int GetEntry() const;

private:
	int Entry;
};
