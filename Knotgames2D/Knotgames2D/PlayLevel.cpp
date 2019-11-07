#include "PlayLevel.h"
#include "Scene.h"
#include "Editor.h"
#include <iostream>
#include "Program.h"
#include "SaveNLoad.h"



void PlayLevel::Start()
{
	if (engine == NULL) engine = Engine::Instanciate();

	/*
	// add buttons
	buttons[0] = Button("start", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, engine->screenRes.y / 2));
	buttons[1] = Button("Editor", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 30 + engine->screenRes.y / 2));
	buttons[2] = Button("Credits", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 60 + engine->screenRes.y / 2));
	buttons[3] = Button("Quit", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 90 + engine->screenRes.y / 2));
	buttonCount = 4;
	*/
	
	// wall collidrs
	
	// floor
	sides[0] = new GameObject(sf::Vector2f(engine->screenRes.x * 0.5f, engine->screenRes.y + 16), "floor.png");
	sides[0]->rb->isKinamatic = true;
	// roof
	sides[1] = new GameObject(sf::Vector2f(engine->screenRes.x * 0.5f, -16), "floor.png");
	sides[1]->rb->isKinamatic = true;
	
	// left
	sides[2] = new GameObject(sf::Vector2f(-16, engine->screenRes.y * 0.5f), "wall.png");
	sides[2]->rb->isKinamatic = true;
	// right
	sides[3] = new GameObject(sf::Vector2f(engine->screenRes.x + 16, engine->screenRes.y * 0.5f), "wall.png");
	sides[3]->rb->isKinamatic = true;
	
	
	
	// ball
	ball = new GameObject(sf::Vector2f(- 150 + engine->screenRes.x * 0.5f, 450), "redBall.png");
	ball->rb->gravityOn = false;
	ball->rb->velocity = sf::Vector2f(-2, -20);
	ball->rb->elasticity = 1;

	// test brick/ future puck
	testBrick = new GameObject(sf::Vector2f(engine->screenRes.x * 0.5f, 450), "block.png");
	testBrick->rb->gravityOn = false;
	//testBrick->rb->velocity = sf::Vector2f(-2, -5);
	//testBrick->rb->isKinamatic = true;

	LoadTiles();
}

void PlayLevel::LoadTiles()
{
	TileFormat tileSet = SaveNLoad::LoadTileFormat("test object");
	for (int i = 0; i < 108; i++)
	{
		if (tileSet.tiles[i] != 0) 
		{
			int y = (int)i / 12;
			int x = i - (12 * y);
			//engine->AddRenderer("brickRed.png", sf::Vector2f(x * 64,y * 32));
			// make game object
			tiles[i] = new GameObject(sf::Vector2f((x * 64) + 32, (y * 32) + 16), "brickRed.png");
			tiles[i]->rb->isKinamatic = true;
		}
	}
}

void PlayLevel::Play()
{
	// game escape button
	
}

void PlayLevel::Physics()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Program::Instanciate()->ShiftScene(0);
	}
	sf::Vector2f puckOffset = sf::Vector2f(sf::Mouse::getPosition(*engine->window).x - testBrick->rb->image->getPosition().x, 
		450 - testBrick->rb->image->getPosition().y);
	if(testBrick->rb->image->getPosition().x < 64)
	{
		testBrick->rb->image->setPosition(sf::Vector2f(64, testBrick->rb->image->getPosition().y));
	}
	/*
	else if (puckOffset.x > engine->screenRes.x - 64) 
	{
		puckOffset.x = engine->screenRes.x - 64;
	}
	*/
	testBrick->rb->velocity = sf::Vector2f(puckOffset.x / 10, puckOffset.y/5);
}

void PlayLevel::OnGUI()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*engine->window);
	/*
	for (int i = 0; i < buttonCount; i++)
	{
		bool state = buttons[i].Run(engine->window, &mousePos);
		if (state)
		{
			GUIActions(i);
			std::cout << i << std::endl;
		}
	}
	*/
}

void PlayLevel::GUIActions(int buttonID)
{
	switch (buttonID)
	{
	case 0:

		break;

	case 1:
		//	program->ShiftScene(2);
		Program::Instanciate()->ShiftScene(1);
		break;

	default:
		break;
	}
}

void PlayLevel::Close()
{
	// clear all game objet
}
