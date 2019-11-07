#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	enum MyEnum
	{
		idle,
		hover,
		click,
	};
private:
	static sf::Font* font;
	std::string name;
	sf::Text text;
	sf::RectangleShape rect;

public:
	bool active;

	Button();

	Button(std::string newName, sf::Color color, sf::Vector2f pos);
	bool Run(sf::RenderWindow* window, sf::Vector2i* mousePos);
	bool IsOver(sf::Vector2i* pos);
};

