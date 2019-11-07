#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Rigidbody.h"


class Engine
{
private:
	static Engine* instance;

	sf::Vector2f offset;
	sf::Vector2f actionNormal;
	bool initialized;
	float nextDrawTime;
	float nextPhysicsTime;
	sf::Clock clock;

	// Physics
	Rigidbody rbd[300];


	// Drawing 
	sf::Sprite Renderers[300];
	sf::RectangleShape GUILines[100];


	void Init();

	void Physics();

	bool AABBCheck(sf::Vector2f lp, sf::FloatRect b1, sf::FloatRect b2);

	void DrawScene();

	void DrawGUI();

public :
	int renderCount = 300;
	sf::Vector2f screenRes = sf::Vector2f(768, 600);
	sf::Texture* GetTexture(const std::string& path);
	float delta;
	int frameRate = 30;
	int physicsRate = 30;

	sf::RenderWindow* window;
	sf::Event* evnt;
	sf::Sprite* sprite;

	// textures
	sf::Texture* blankTexture;
	std::map<std::string, sf::Texture> texDict;
	// functions
	static Engine* Instanciate();
	void Test();
	void Run();
	void Reset();
	sf::Sprite* AddRenderer(std::string path, sf::Vector2f pos);
	void AddGUI(float length, sf::Vector2f dir, sf::Vector2f orig);
	Rigidbody* RegRigidbody();
};

