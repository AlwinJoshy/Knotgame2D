#include "Engine.h"
#include <iostream>
#include "Editor.h"
#include "InputK.h"
#include "SaveNLoad.h"
#include "Program.h"

void Editor::Start()
{
	// setting brick type
	currentBrick = 1;

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
	buttons[2] = Button("Brick", sf::Color(0, 0, 0, 255), sf::Vector2f(60, 60 + engine->screenRes.y / 2));
	buttons[3] = Button("Stone", sf::Color(0, 0, 0, 255), sf::Vector2f(180, 60 + engine->screenRes.y / 2));
	buttons[4] = Button("Crystal", sf::Color(0, 0, 0, 255), sf::Vector2f(310, 60 + engine->screenRes.y / 2));

	buttonCount = 5;

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

	case 2:
		currentBrick = 1;
		break;

	case 3:
		currentBrick = 2;
		break;

	case 4:
		currentBrick = 3;
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
					if (tilesArray[tileIndex] == 0 || tilesArray[tileIndex] != currentBrick)
					{
						if (tilesArray[tileIndex] != 0)
						{
						//	tilesArray[tileIndex] = 0;
							tilesSprites[tileIndex]->setTexture(*engine->blankTexture);
						}

						tilesArray[tileIndex] = currentBrick;

						switch (currentBrick)
						{
						// brick
						case 1 :
							tilesSprites[tileIndex] = engine->AddRenderer("brickRed.png", sf::Vector2f(xTilePos + 32, yTilePos + 16));
							break;

						// stone
						case 2:
							tilesSprites[tileIndex] = engine->AddRenderer("stone.png", sf::Vector2f(xTilePos + 32, yTilePos + 16));
							break;

						// crystal
						case 3:
							tilesSprites[tileIndex] = engine->AddRenderer("crystal.png", sf::Vector2f(xTilePos + 32, yTilePos + 16));
							break;

						default:
							break;
						}
						
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