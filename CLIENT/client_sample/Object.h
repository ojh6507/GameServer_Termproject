#pragma once
#include "stdafx.h"
#include "AnimateSprite.h"


extern sf::Font g_font;

class OBJECT
{


public:
	OBJECT() {
		m_showing = false;
		set_name("NONAME");
		m_mess_end_time = chrono::system_clock::now();
	}

	
public:
	//virtual void a_move(int x, int y) = 0;
	//virtual void a_draw() = 0;

	virtual void move(int x, int y) = 0;
	virtual void Update(float deltTime, int dir) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	
	/*void draw() {
		if (false == m_showing) return;
		float rx = (m_x - g_left_x) * 65.0f + 1;
		float ry = (m_y - g_top_y) * 65.0f + 1;
		m_sprite.setPosition(rx, ry);
		g_window->draw(m_sprite);
		auto size = m_name.getGlobalBounds();
		if (m_mess_end_time < chrono::system_clock::now()) {
			m_name.setPosition(rx + 32 - size.width / 2, ry - 10);
			g_window->draw(m_name);
		}
		else {
			m_chat.setPosition(rx + 32 - size.width / 2, ry - 10);
			g_window->draw(m_chat);
		}
	}*/

	void set_name(const char str[]) {
		m_name.setFont(g_font);
		m_name.setString(str);
		if (id < MAX_USER) m_name.setFillColor(sf::Color(255, 255, 255));
		else m_name.setFillColor(sf::Color(255, 255, 0));
		m_name.setStyle(sf::Text::Bold);
	}
	void set_chat(const char str[]) {
		m_chat.setFont(g_font);
		m_chat.setString(str);
		m_chat.setFillColor(sf::Color(255, 255, 255));
		m_chat.setStyle(sf::Text::Bold);
		m_mess_end_time = chrono::system_clock::now() + chrono::seconds(1);
	}
	void show() {
		m_showing = true;
	}
	void hide() {
		m_showing = false;
	}

public:
	int id;
	int m_x, m_y;
	char name[NAME_SIZE];
protected:
	bool m_showing;
	sf::Text m_name;
	sf::Text m_chat;
	std::chrono::system_clock::time_point m_mess_end_time;
};

class Character : public OBJECT{

public:
	Character(){}
	Character(sf::Texture& t, sf::Vector2u imgCount, float switchTime, float speed);
public:
	virtual void move(int x, int y) override;
	virtual void Update(float deltaTime, int dir) override;
	virtual void Draw(sf::RenderWindow& window) override;

public:
	sf::Vector2f pos;
	sf::RectangleShape body;
	AnimateSprite animation;
	unsigned int row;
	float speed;
	bool faceRight;


};

class BoardBlock :public OBJECT
{
public:
	BoardBlock() {}
	BoardBlock(sf::Texture& t, sf::Vector2u imgCount, float switchTime, int x, int y);
public:
	virtual void move(int x, int y) override;
	virtual void Update(float deltaTime, int dir) override;
	virtual void Draw(sf::RenderWindow& window) override;

public:
	sf::Vector2f pos;
	sf::RectangleShape body;
	AnimateSprite animation;
};