#include "SFML/Graphics.hpp"
#include <cmath>
#include "MyMath.h"

float MyMath::Dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f MyMath::Normalize(sf::Vector2f v)
{
	float h = sqrt(v.x * v.x + v.y * v.y);
	return sf::Vector2f(v.x / h, v.y/ h);
}