#pragma once

//Cardinal directions
enum direction { NORTH = 0, EAST, SOUTH, WEST, COUNT };

namespace tileType
{
	/*
	Air			-- 'Empty' tile
	Solid Air	-- Visually appears as an air tile, but cannot be passed through
	Brick		-- Tile breakable by bomb
	Tile		-- Unbreakable tile
	Door Closed	-- Effectively the same as a brick tile, but it becomes a door open tile when broken
	Door Open	-- Exit door tile
	Powerup		-- For powerups..?
	*/
	enum ID { AIR = 0, SOLID_AIR, BRICK, TILE, DOOR_CLOSED, DOOR_OPEN, POWERUP };
}