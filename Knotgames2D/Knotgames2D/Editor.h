#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"

class Editor : public Scene
{
private:
	int tilesArray[108];
	sf::Sprite* tilesSprites[108];

public :
	virtual void Start();
	void OnGUI();
	void GUIActions(int buttonID);
	virtual void Play();
	void Save();
	virtual void Close();
};

