#include "Valcom.h"
#include <math.h>


Valcom::Valcom(const sf::Vector2i& tile)
{
	init(tile, directions::NORTH);
}


Valcom::Valcom(const sf::Vector2i& tile, const directions& face)
{
	init(tile, face);
}


void Valcom::init(const sf::Vector2i& tile, const directions& face)
{
	heading = face;
	moveSpeed = 1.f;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 0, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(* t, 0, 16 * 1, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 2, 16, 16, 5);

	if (face == directions::WEST)
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
	case directions::NORTH:
		if (tilePos.y >= 0 && sprite.getPosition().y >= 100 &&
			tilemap[tilePos.x + 1][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(0, -moveSpeed);
		else
			heading = directions::SOUTH;
		break;
	case directions::SOUTH:
		if (tilePos.y < mapSize.y - 2 && sprite.getPosition().y < 48 * 12 + 100 &&
			tilemap[tilePos.x + 1][tilePos.y + 2]->getType() == tileType::AIR)
			sprite.move(0, moveSpeed);
		else
			heading = directions::NORTH;
		break;
	case directions::EAST:
		if (tilePos.x >= 0 && sprite.getPosition().x < 48 * 30 &&
			tilemap[tilePos.x + 2][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(moveSpeed, 0);
		else
		{
			heading = directions::WEST;
			curAnim = animIndex::LEFT;
		}
		break;
	case directions::WEST:
		if (tilePos.x < mapSize.x - 1 && sprite.getPosition().x >= 0 &&
			tilemap[tilePos.x + 1][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(-moveSpeed, 0);
		else
		{
			heading = directions::EAST;
			curAnim = animIndex::RIGHT;
		}
	}

	//Change direction
	if (rand() % 10 < 8 && debounce >= DEBOUNCE_MAX)
	{
		if ((heading == directions::NORTH || heading == directions::SOUTH) &&
			abs(sprite.getPosition().y -
				tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().y) <
			getClippingMargin() && sprite.getPosition().y >=
			tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().y)
		{
			//Go West
			if (rand() % 2)
			{
				if (tilePos.x > 1 &&
					tilemap[tilePos.x][tilePos.y + 1]->getType() == tileType::AIR)
				{
					heading = directions::WEST;
					debounce = 0;
				}
			}
			//Go East
			else
			{
				if (tilePos.x < mapSize.x - 2 &&
					tilemap[tilePos.x + 2][tilePos.y + 1]->getType() == tileType::AIR)
				{
					heading = directions::EAST;
					debounce = 0;
				}
			}
		}
		else if ((heading == directions::EAST || heading == directions::WEST) &&
			abs(sprite.getPosition().x -
				tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().x) <
			getClippingMargin() && sprite.getPosition().x >=
			tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().x)
		{
			//Go North
			if (rand() % 2)
			{
				if (tilePos.y > 1 &&
					tilemap[tilePos.x + 1][tilePos.y]->getType() == tileType::AIR)
				{
					heading = directions::NORTH;
					debounce = 0;
				}
			}
			//Go South
			else
			{
				if (tilePos.y < mapSize.y - 2 &&
					tilemap[tilePos.x + 1][tilePos.y + 2]->getType() == tileType::AIR)
				{
					heading = directions::SOUTH;
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