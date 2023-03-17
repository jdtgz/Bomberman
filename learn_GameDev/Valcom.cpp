#include "Valcom.h"
#include <math.h>


Valcom::Valcom(const sf::Vector2i& tile)
{
	init(tile, dir::NORTH);
}


Valcom::Valcom(const sf::Vector2i& tile, const dir& face)
{
	init(tile, face);
}


void Valcom::init(const sf::Vector2i& tile, const dir& face)
{
	heading = face;
	moveSpeed = 1.f;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 0, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(* t, 0, 16 * 1, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 2, 16, 16, 5);

	if (face == dir::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(48 * tile.x, 100 + 48 * tile.y);
}


void Valcom::move(Tile* tilemap[33][15],
	const sf::Vector2i& mapSize)
{
	//Update current tile position
	tilePos = sf::Vector2i(sprite.getPosition().x / 48,
		(sprite.getPosition().y - 100) / 48);
	
	//Update current position or change heading
	switch (heading)
	{
	case NORTH:
		if (tilePos.y >= 0 && sprite.getPosition().y >= 100 &&
			tilemap[tilePos.x + 1][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(0, -moveSpeed);
		else
			heading = SOUTH;
		break;
	case SOUTH:
		if (tilePos.y < mapSize.y - 2 && sprite.getPosition().y < 48 * 12 + 100 &&
			tilemap[tilePos.x + 1][tilePos.y + 2]->getType() == tileType::AIR)
			sprite.move(0, moveSpeed);
		else
			heading = NORTH;
		break;
	case EAST:
		if (tilePos.x >= 0 && sprite.getPosition().x < 48 * 30 &&
			tilemap[tilePos.x + 2][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(moveSpeed, 0);
		else
		{
			heading = WEST;
			curAnim = animIndex::LEFT;
		}
		break;
	case WEST:
		if (tilePos.x < mapSize.x - 1 && sprite.getPosition().x >= 0 &&
			tilemap[tilePos.x + 1][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(-moveSpeed, 0);
		else
		{
			heading = EAST;
			curAnim = animIndex::RIGHT;
		}
	}

	//Change direction
	if (rand() % 10 < 8 && debounce >= DEBOUNCE_MAX)
	{
		if ((heading == dir::NORTH || heading == dir::SOUTH) &&
			abs(sprite.getPosition().y -
				tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().y) < getClippingMargin() &&
			sprite.getPosition().y >= tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().y)
		{
			//Go West
			if (rand() % 2)
			{
				if (tilePos.x > 1 &&
					tilemap[tilePos.x][tilePos.y + 1]->getType() == tileType::AIR)
				{
					heading = dir::WEST;
					debounce = 0;
				}
			}
			//Go East
			else
			{
				if (tilePos.x < mapSize.x - 2 &&
					tilemap[tilePos.x + 2][tilePos.y + 1]->getType() == tileType::AIR)
				{
					heading = dir::EAST;
					debounce = 0;
				}
			}
		}
		else if ((heading == dir::EAST || heading == dir::WEST) &&
			abs(sprite.getPosition().x -
				tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().x) < getClippingMargin() &&
			sprite.getPosition().x >= tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().x)
		{
			//Go North
			if (rand() % 2)
			{
				if (tilePos.y > 1 &&
					tilemap[tilePos.x + 1][tilePos.y]->getType() == tileType::AIR)
				{
					heading = dir::NORTH;
					debounce = 0;
				}
			}
			//Go South
			else
			{
				if (tilePos.y < mapSize.y - 2 &&
					tilemap[tilePos.x + 1][tilePos.y + 2]->getType() == tileType::AIR)
				{
					heading = dir::SOUTH;
					debounce = 0;
				}
			}
		}
	}
}


void Valcom::update(const float& dt)
{
	debounce++;

	anims[int(curAnim)].update(dt);
	anims[int(curAnim)].applyToSprite(sprite);

	return;
}


double Valcom::getClippingMargin() const
{
	return 0.8;
}


Valcom::~Valcom()
{

}