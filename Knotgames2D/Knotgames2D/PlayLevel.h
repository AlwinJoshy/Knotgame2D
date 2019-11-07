#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include "GameObject.h"

class PlayLevel :public Scene
{
	GameObject* sides[4];
	GameObject* tiles[108];
	GameObject* ball;
	GameObject* testBrick;

public:
	virtual void Start();
	void LoadTiles();
	virtual void Play();
	void Physics();
	void OnGUI();
	void GUIActions(int buttonID);
	virtual void Close();
};

