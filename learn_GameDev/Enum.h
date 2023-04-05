#pragma once

enum direction { NORTH = 0, EAST, SOUTH, WEST, COUNT };

namespace tileType
{
	enum ID { AIR = 0, SOLID_AIR, BRICK, TILE, DOOR_CLOSED, DOOR_OPEN, POWERUP };
}