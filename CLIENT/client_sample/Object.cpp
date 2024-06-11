#include "Object.h"

Character::Character(sf::Texture& t, sf::Vector2u imgCount, float switchTime, float speed)
	:animation(t, imgCount, switchTime), speed{ speed }, row{}, faceRight{}
{
	body.setSize(sf::Vector2f(150, 150));
	body.setPosition(4,4);
	body.setTexture(&t);
	t.setRepeated(true);

	idleTexture = new sf::Texture;
	walkTexture = new sf::Texture;
	attack_1Texture = new sf::Texture;
	attack_2Texture = new sf::Texture;

	idleTexture->loadFromFile("Assets/Samurai/Idle.png");
	walkTexture->loadFromFile("Assets/Samurai/Walk.png");
	attack_1Texture->loadFromFile("Assets/Samurai/Attack_1.png");
	attack_2Texture->loadFromFile("Assets/Samurai/Attack_2.png");

	isSpriteUpdated = false;
}

Character::~Character()
{}

void Character::move(int x, int y)
{
	pos.x = x;
	pos.y = y;
	body.move(pos);
}

void Character::Update(float deltaTime, int dir)
{
	sf::Vector2f movement(0.f, 0.f);
	if (isSpriteUpdated) {
		if (stat == STAT::WALK) {
			animation.ChangeSprite(*walkTexture, sf::Vector2u(8, 1), 0.1f);
			body.setTexture(walkTexture);
			walkTexture->setRepeated(true);
		}
		if (stat == STAT::IDLE) {
			animation.ChangeSprite(*idleTexture, sf::Vector2u(6, 1), 0.1f);
			body.setTexture(idleTexture);
			idleTexture->setRepeated(true);
		}
		if (stat == STAT::ATTACK_1) {
			animation.ChangeSprite(*attack_1Texture, sf::Vector2u(6, 1), 0.05f);
			body.setTexture(attack_1Texture);
			attack_1Texture->setRepeated(true);
		}
		if (stat == STAT::ATTACK_2) {
			animation.ChangeSprite(*attack_2Texture, sf::Vector2u(4, 1), 0.05f);
			body.setTexture(attack_2Texture);
			attack_2Texture->setRepeated(true);
		}
		isSpriteUpdated = false;
	}
	
	updateCharacterState(movement, deltaTime, dir);
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
void Character::updateCharacterState(sf::Vector2f& movement, float deltaTime, int dir)
{

	switch (dir) {
	case 2:
		new_stat = STAT::WALK;
		movement.x -= speed * deltaTime;
		break;
	case 3:
		new_stat = STAT::WALK;
		movement.x += speed * deltaTime;
		break;
	case 0:
		new_stat = STAT::WALK;
		movement.y -= speed * deltaTime;
		break;
	case 1:
		new_stat = STAT::WALK;
		movement.y += speed * deltaTime;
		break;
	case 4:
		new_stat = STAT::ATTACK_1;
		break;
	case 5:
		new_stat = STAT::ATTACK_2;
		break;
	default:
		new_stat = STAT::IDLE;
		break;
	}
	
	if (new_stat != stat) {
		isSpriteUpdated = true;
		stat = new_stat;
	}


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
