#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>

class Rigidbody
{
public:
	bool isCreated = false;
	bool isKinamatic = false;
	bool gravityOn = true;
	bool isHit = false;
	float mass = 1;
	float drag = 0;
	float elasticity = 0.5f;
	sf::Vector2f actionNormal;
	sf::Vector2f recVelocity;
	sf::Vector2f velocity;
	sf::Vector2f offset;
	sf::Sprite* image;

	//void SetValues();
	Rigidbody();
};

