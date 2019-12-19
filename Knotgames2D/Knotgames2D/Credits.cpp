#include "Credits.h"
#include "Scene.h"
#include "Editor.h"
#include <iostream>
#include "Program.h"


void Credits::Start()
{
	if (engine == NULL) engine = Engine::Instanciate();
	// set title
	creditImage = sf::Sprite();
	sf::Texture* img = engine->GetTexture("credit.png");
	creditImage.setTexture(*img);
	creditImage.setOrigin((sf::Vector2f)img->getSize() * 0.5f);
	creditImage.setPosition(sf::Vector2f(engine->screenRes.x / 2, 100));
}


void Credits::Play()
{
	// game escape button

}

void Credits::Physics()
{

}

void Credits::OnGUI()
{
	engine->window->draw(creditImage);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Program::Instanciate()->ShiftScene(0);
	}

}

void Credits::GUIActions(int buttonID)
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

void Credits::Close()
{
	/*
	// clear all game objet
	for (int i = 0; i < 108; i++)
	{
		if (tiles[i] != nullptr)
		{
			tiles[i]->alive = false;
			tiles[i]->pic->setTexture(*engine->blankTexture);
			//	delete(tiles[i]->rb);

			//	delete(tiles[i]);
		}
		
		//	delete(tiles[i]);
		//	tiles[i]->rb->isKinamatic = true;
	}

	*/
}

