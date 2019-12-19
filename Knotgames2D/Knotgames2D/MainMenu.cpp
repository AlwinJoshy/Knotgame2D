#include "MainMenu.h"
#include "Program.h"
#include <iostream>


void MainMenu::Start()
{
	if (engine == NULL) engine = Engine::Instanciate();
	// set title
	title = sf::Sprite();
	sf::Texture* img = engine->GetTexture("gameTitle.png");
	title.setTexture(*img);
	title.setOrigin((sf::Vector2f)img->getSize() * 0.5f);
	title.setPosition(sf::Vector2f(engine->screenRes.x / 2, 100));

	// add buttons
	buttons[0] = Button("Start", sf::Color(0, 0, 0,255), sf::Vector2f(engine->screenRes.x/2, engine->screenRes.y / 2));
	buttons[1] = Button("Editor", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 30 + engine->screenRes.y / 2));
	buttons[2] = Button("Credits", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 60 + engine->screenRes.y / 2));
	buttons[3] = Button("Quit", sf::Color(0, 0, 0, 255), sf::Vector2f(engine->screenRes.x / 2, 90 + engine->screenRes.y / 2));
	buttonCount = 4;
}

void MainMenu::Play()
{

}

void MainMenu::OnGUI()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*engine->window);

	// display title
	engine->window->draw(title);

	// run buttons
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

void MainMenu::GUIActions(int buttonID)
{
	switch (buttonID)
	{
		// open game scene
		case 0:
			Program::Instanciate()->ShiftScene(2);
			break;

		// Editor
		case 1:
			Program::Instanciate()->ShiftScene(1);
			break;

		// Credits
		case 2:
			Program::Instanciate()->ShiftScene(3);
			break;

		// Quit game
		case 3:
			Engine::Instanciate()->stayAlive = false;
			break;

		default:
			break;
	}
}

void MainMenu::Close()
{

}