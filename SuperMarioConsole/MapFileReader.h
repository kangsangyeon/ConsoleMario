#pragma once

#include "ConsoleMario.h"
#include <string>
#include <vector>

class MapFileReader
{
public:
	static bool ReadFromFile(std::string _fileNameBase, int _entry, class Map** _outMap, class Player** _outPlayer, std::vector<class PhysicsBody*>** _outPhysicsBodies, std::vector<class StaticObject*>** _outStaticObjects);

};
