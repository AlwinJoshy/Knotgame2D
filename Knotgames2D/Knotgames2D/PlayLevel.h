#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include "GameObject.h"

class PlayLevel :public Scene
{
	GameObject* testBrick;
	GameObject* sides[4];
	GameObject* tiles[108];
	GameObject* ball;

public:
	virtual void Start();
	void LoadTiles();
	virtual void Play();
	void Physics();
	void OnGUI();
	void GUIActions(int buttonID);
	virtual void Close();
};

