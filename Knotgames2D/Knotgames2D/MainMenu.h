#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"

class MainMenu : public Scene
{

public:
	sf::Sprite title;
	virtual void Start();
	virtual void Play();
	void OnGUI();
	void GUIActions(int buttonID);
	virtual void Close();
};