#include "Engine.h"
#include <iostream>
#include "Editor.h"
#include "InputK.h"
#include "SaveNLoad.h"
#include "Program.h"

void Editor::Start()
{
	// adding gridlines..
	engine = Engine::Instanciate();
		   
	int xRepeat = (engine->screenRes.y / 32) / 2;

	for (int i = 0; i < xRepeat; i++)
	{
		engine->AddGUI(engine->screenRes.x, sf::Vector2f(0, 1), sf::Vector2f(0, (i + 1) * 32));
	}

	int yRepeat = (engine->screenRes.x / 64);
	for (int i = 0; i < yRepeat; i++)
	{
		engine->AddGUI(xRepeat * 32, sf::Vector2f(1, 0), sf::Vector2f((i + 1) * 64, 0));
	}
	
	// create buttons

	buttons[0] = Button("Save", sf::Color(0, 0, 0, 255), sf::Vector2f(60, engine->screenRes.y / 2));
	buttons[1] = Button("Exit", sf::Color(0, 0, 0, 255), sf::Vector2f(60, 30 + engine->screenRes.y / 2));
	//buttons[2] = Button("Credits", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 60 + engine->screenRes.y / 2));
	//buttons[3] = Button("Quit", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 90 + engine->screenRes.y / 2));
	
	buttonCount = 2;

	std::cout << "Editor Started..." << std::endl;

	
}

void Editor::OnGUI()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*engine->window);

	for (int i = 0; i < buttonCount; i++)
	{
		bool state = buttons[i].Run(engine->window, &mousePos);
		if (state)
		{
			GUIActions(i);
			std::cout << i << std::endl;
		}
	}
}

void Editor::GUIActions(int buttonID)
{
	switch (buttonID)
	{
	case 0:
		Save();
		break;

	case 1:
		Program::Instanciate()->ShiftScene(0);
		break;

	default:
		break;
	}
}

void Editor::Play()
{
	// place tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!InputK::leftMousePressed)
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(*engine->window);
			
			if (localPosition.x * localPosition.y >= 0) 
			{
				float xTilePos = localPosition.x - (localPosition.x % 64);
				float yTilePos = localPosition.y - (localPosition.y % 32);

				int tileIndex = (12 * (yTilePos / 32)) + xTilePos / 64;

				// if within bounds
				if (tileIndex >= 0 && tileIndex < 108)
				{
					InputK::leftMousePressed = true;
					// if slot empty
					if (tilesArray[tileIndex] == 0)
					{
						tilesArray[tileIndex] = 1;
						tilesSprites[tileIndex] = engine->AddRenderer("brickRed.png", sf::Vector2f(xTilePos + 32, yTilePos + 16));
					}
					// if slot occupied
					else 
					{
						tilesArray[tileIndex] = 0;
						tilesSprites[tileIndex]->setTexture(*engine->blankTexture);
					}
				}
			}
		}
	}

	else 
	{
		InputK::leftMousePressed = false;
	}

}

void Editor::Save() 
{
	SaveNLoad::SaveTileFormat("test object", tilesArray);
}

void Editor::Close()
{
	std::cout << "Editor Closed..." << std::endl;

	for (size_t i = 0; i < 108; i++)
	{
		if (tilesSprites[i] != nullptr)
		{
			tilesArray[i] = 0;
			tilesSprites[i]->setTexture(*engine->blankTexture);
		}
	}

}