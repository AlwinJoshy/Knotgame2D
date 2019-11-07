#include "Button.h"
#include "Engine.h"
#include <iostream>
#include "InputK.h"

sf::Font* Button::font = nullptr;

Button::Button() 
{
}

Button::Button(std::string newName,sf::Color color, sf::Vector2f pos)
{
	if (font == NULL) 
	{
		active = true;
		font = new sf::Font();
		font->loadFromFile("ARCADECLASSIC.TTF");
	}
	name = newName;
	text.setFont(*font);
	text.setString(name);
	text.setFillColor(color);
	sf::FloatRect textBox = text.getGlobalBounds();
	text.setOrigin(sf::Vector2f(textBox.width / 2, textBox.height / 2));
	text.setPosition(pos);

	
	rect.setFillColor(sf::Color(255, 255, 255, 255));
	rect.setSize(sf::Vector2f(10 + textBox.width, 10 + textBox.height));
	sf::FloatRect rectBox = rect.getGlobalBounds();
	rect.setOrigin(0, 0);
	rect.setOrigin(sf::Vector2f(rectBox.width / 2, 0));
	

	rect.setPosition(pos);
	
}

bool Button::Run(sf::RenderWindow* window, sf::Vector2i* mousePos)
{
	bool state = false;
	if (IsOver(mousePos)) 
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			// on click
			if (!InputK::leftMousePressed)
			{
				rect.setFillColor(sf::Color(255, 255, 255, 255));
				InputK::leftMousePressed = true;
				state = true;
			}
		}
		else
		{	
				//on hover
				rect.setFillColor(sf::Color(128, 128, 128, 255));
				InputK::leftMousePressed = false;
				state = false;
		}
	}

	else rect.setFillColor(sf::Color(255, 255, 255, 255));

	window->draw(rect);
	window->draw(text);
	return state;
}

bool Button::IsOver(sf::Vector2i* pos) 
{
	sf::FloatRect size = rect.getGlobalBounds();
	if (pos->y >= size.top && pos->y <= size.top + size.height &&
		pos->x >= size.left&& pos->x <= size.left + size.width) return true;
	return false;
	
}