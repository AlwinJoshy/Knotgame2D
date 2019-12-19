#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"

class Credits :public Scene
{


public:
	sf::Sprite creditImage;
	virtual void Start();
	void LoadTiles();
	virtual void Play();
	void Physics();
	void OnGUI();
	void GUIActions(int buttonID);
	virtual void Close();
};

