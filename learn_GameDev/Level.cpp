#include "Level.h"
#include <math.h>
#include "Valcom.h"


Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = 0, yPos = 100;
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (y == 0 || x == 0 || y == MAP_HEIGHT - 1 || x == MAP_LENGTH - 1)
				tilemap[x][y] = new Tile(xPos, yPos, tileType::AIR);
			else if (x % 2 != 0 && y % 2 != 0)
				tilemap[x][y] = new Tile(xPos, yPos, tileType::TILE);
			else
				tilemap[x][y] = new Tile(xPos, yPos, tileType::AIR);
			yPos += 48;
		}
		xPos += 48;
		yPos = 100;
	}

	//Create tile border
	xPos = -48;
	yPos = 100;
	for (int i = 0; i < BORDER_COUNT; i++)
	{
		if (i < MAP_LENGTH + 2)
		{
			border[i] = new Tile(xPos, 48, tileType::TILE);
			xPos += 48;
		}
		else if (i < MAP_LENGTH + MAP_LENGTH + 4)
		{
			border[i] = new Tile(xPos - 48, (MAP_HEIGHT + 2) * 48, tileType::TILE);
			xPos -= 48;
		}
		else
		{
			if (i % 2 != MAP_LENGTH % 2)
				border[i] = new Tile(-48, yPos, tileType::TILE);
			else
			{
				border[i] = new Tile(MAP_LENGTH * 48, yPos, tileType::TILE);
				yPos += 48;
			}
		}
	}


	enemies.push_back(new Valcom(sf::Vector2i(0, 0)));
}


Level::~Level()
{
	//Unallocate tilemap memory
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			delete tilemap[x][y];

	for (int i = 0; i < BORDER_COUNT; i++)
		delete border[i];

	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
}


void Level::generate(const int& levelNum)
{
	int random = 0, randX = 0, randY = 0, totalSoftBlock = 0, i = 0;
	//int enemies = 0;

	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (!(x % 2 != 0 && y % 2 != 0) && x + y > 1) // keep top left corner open
			{
				random = rand() % 4;
				if (random == 1)
				{
					totalSoftBlock++;
					tilemap[x][y]->setTile(tileType::BRICK);
				}
			}
		}
	}

	powerup->setPosition(48, 48); 

	/*
	while(enemies < 6)
	{
	randX = (rand() % (mapLength - 2)) + 1
	randY = (rand() % (mapHeight - 2)) + 1

	if(tilemap[x][y]->getType() == 0 && x + y > 1)
		//Create enemy at x,y
	}

	//PowerUp Set
	random = rand % totalSoftBlock; //pick random soft block

	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			if(tilemap[x][y]->getType() == 1)
				i++;
			if(random == i)
				// set x,y to a powerup
		}
	}

	//Exit Set
	random = rand % totalSoftBlock; //pick random soft block
	i = 0;

	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			if(tilemap[x][y]->getType() == 1)
				i++;
			if(random == i)
				// set x,y to a exit
		}
	}
  */
}


void Level::end()
{
	//will check for level end
}


int Level::getLength() const
{
	return MAP_LENGTH;
}


int Level::getHeight() const
{
	return MAP_HEIGHT;
}


// draw all the objects and emeies onto the screen 
void Level::draw(sf::RenderWindow& window) const
{
	//Print the tiles to the window
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->draw(window);

	for (int i = 0; i < BORDER_COUNT; i++)
		border[i]->draw(window);
	
	for(int i = 0; i < enemies.size(); i++)
		enemies[i]->draw(window);

	powerup->draw(window); 
}


//Detect collisions between player and tile
void Level::collisions(Player& plr)
{
	getClosestTile(plr.getSprite().getPosition());

	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->detectCollision(plr,
				y > 0 ? tilemap[x][y - 1]->getType() : tileType::TILE,
				y < MAP_HEIGHT - 1 ? tilemap[x][y + 1]->getType() : tileType::TILE,
				x > 0 ? tilemap[x - 1][y]->getType() : tileType::TILE,
				x < MAP_LENGTH - 1 ? tilemap[x + 1][y]->getType() : tileType::TILE);

	for (int i = 0; i < BORDER_COUNT; i++)
		border[i]->detectCollision(plr,
			i < MAP_LENGTH + MAP_LENGTH + 4 && i >= MAP_LENGTH + 2 ?
			tileType::AIR : tileType::TILE,
			i < MAP_LENGTH + 2 ? tileType::AIR : tileType::TILE,
			i % 2 == MAP_LENGTH % 2 && i >= MAP_LENGTH + MAP_LENGTH + 4 ?
			tileType::AIR : tileType::TILE,
			i % 2 != MAP_LENGTH % 2 && i >= MAP_LENGTH + MAP_LENGTH + 4 ?
			tileType::AIR : tileType::TILE);
}


Tile* Level::getTilemap()
{
	return tilemap[0][0];
}


sf::Vector2i Level::getClosestTile(const sf::Vector2f& v2)
{
	int x = 0, y = 0;
	Tile* closestTile = tilemap[x][y];

	for (int a = 0; a < MAP_LENGTH; a++)
	{
		for (int b = 0; b < MAP_HEIGHT; b++)
		{
			if (sqrt(pow(closestTile->getPosition().x - v2.x, 2) +
				pow(closestTile->getPosition().y - v2.y, 2)) >
				sqrt(pow(tilemap[a][b]->getPosition().x - v2.x, 2) +
					pow(tilemap[a][b]->getPosition().y - v2.y, 2)))
			{
				closestTile = tilemap[a][b];
				x = a;
				y = b;
			}
		}
	}

	return sf::Vector2i(x, y);
}


void Level::update(const float& dt)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(dt);
		enemies[i]->move(tilemap, sf::Vector2i(MAP_LENGTH, MAP_HEIGHT));
	}
}