#include "GameObject.h"

GameObject::GameObject(sf::Vector2f pos, std::string path)
{
	engine = Engine::Instanciate();

	// add renderer
	pic = engine->AddRenderer(path, pos);
	sf::FloatRect bound = pic->getGlobalBounds();
	pic->setOrigin(bound.width * 0.5f, bound.height * 0.5f);

	// make rigidbody
	rb = engine->RegRigidbody();
	rb->image = pic;

}

GameObject::~GameObject()
{

}
