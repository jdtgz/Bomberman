#pragma once

//global debug variable
const bool DEBUG = true;

//Cardinal directions
enum direction { NORTH = 0, EAST, SOUTH, WEST, COUNT };

enum enemyType { VALCOM = 0, ONEAL, DAHL, MINVO, OVAPE, DORIA, PASS, PONTAN };

namespace tileType
{
	/*
	Air			-- 'Empty' tile
	Solid Air	-- Visually appears as an air tile, but cannot be passed through
	Brick		-- Tile breakable by bomb
	Tile		-- Unbreakable tile
	Door Closed	-- Effectively the same as a brick tile, but it becomes a door open tile when broken
	Door Open	-- Exit door tile
	PowerUp_Hidden -- behaves like a brick, but is a powerUp waiting to be revealed
	PowerUp_Revealed -- PowerUp obj
	*/
	enum ID { AIR = 0, SOLID_AIR, BRICK, TILE, DOOR_CLOSED, DOOR_OPEN, POWERUP_HIDDEN, POWERUP_REVEALED };
}