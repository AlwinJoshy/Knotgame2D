#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include "Engine.h"
#include <iostream>
#include "Rigidbody.h"

class GameObject
{
	Engine* engine;
	sf::Sprite* pic;
public :

	Rigidbody* rb;

	GameObject(sf::Vector2f, std::string path);

	~GameObject();

};

