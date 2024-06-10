#include "Object.h"

Character::Character(sf::Texture& t, sf::Vector2u imgCount, float switchTime, float speed)
	:animation(t, imgCount, switchTime), speed{ speed }, row{}, faceRight{}
{
	body.setSize(sf::Vector2f(100, 100));
	body.setPosition(4,4);
	body.setTexture(&t);
	t.setRepeated(true);

}

void Character::move(int x, int y)
{
	pos.x = x;
	pos.y = y;
	body.move(pos);
}

void Character::Update(float deltaTime, int dir)
{
	sf::Vector2f movement(0.f, 0.f);
	switch (dir)
	{
	case 0:
		movement.y -= speed * deltaTime;
		break;
	case 1:
		movement.y += speed * deltaTime;
		break;
	case 2:
		movement.x -= speed * deltaTime;
		break;
	case 3:
		movement.x += speed * deltaTime;
		break;
	default:

		break;
	}
	if (movement.x == 0) {
		row = 0;
	}
	else {
		row = 1;
		if (movement.x > 0.f) faceRight = true;
		else faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	pos = movement;
	body.move(movement);
}

void Character::Draw(sf::RenderWindow& window)
{
	if (false == m_showing)
	window.draw(body);
}

BoardBlock::BoardBlock(sf::Texture& t, sf::Vector2u imgCount, float switchTime, int x, int y)
	: animation(t, imgCount, switchTime)
{
	body.setTexture(&t);
	body.setTextureRect(sf::IntRect(x, y, TILE_WIDTH, TILE_WIDTH));
	body.setPosition(0, 0);
}

void BoardBlock::move(int x, int y)
{
	pos.x = x;
	pos.y = y;
	body.move(pos);
}

void BoardBlock::Update(float deltaTime, int dir)
{
}

void BoardBlock::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
