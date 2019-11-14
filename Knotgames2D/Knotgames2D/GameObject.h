#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include "Engine.h"
#include <iostream>
#include "Rigidbody.h"

class GameObject
{
	Engine* engine;
	
public :

	Rigidbody* rb;
	sf::Sprite* pic;
	bool alive = false;

	GameObject(sf::Vector2f, std::string path);

	~GameObject();

};

