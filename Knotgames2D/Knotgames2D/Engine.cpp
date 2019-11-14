/*

	Level Editor Script
	a child class of Scene
	
*/

#include "stddef.h"
#include <iostream>
#include "Engine.h"
#include "Program.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "Rigidbody.h"
#include "MyMath.h"
#include <cmath>


sf::CircleShape* cir;

Engine* Engine::instance = NULL;

Engine* Engine :: Instanciate()
{
	if (instance == NULL) 
	{
		instance = new Engine();
	}
		return instance;
}

void Engine:: Test()
{
	std::cout << " Engine Test run..." << std::endl;
}

void Engine::Init()
{
	cir = new sf::CircleShape(5);
	cir->setOrigin(sf::Vector2f(3.5, 3.5));

	window = new sf::RenderWindow(sf::VideoMode(screenRes.x, screenRes.y), "Test Window...", sf::Style::Titlebar);
	evnt = new sf::Event();
	
	blankTexture = GetTexture("blank.png");

	// initialize all renderers
	for (int i = 0; i < 200; i++)
	{
		Renderers[i].setTexture(*blankTexture);
	}

}

void Engine::Physics()
{
	
	// move all objects
	for (int i = 0; i < 300; i++)
	{
		if (rbd[i].isCreated)
		{
			// static or not
			if (!rbd[i].isKinamatic)
			{
				// gravity
				if (rbd[i].gravityOn)rbd[i].velocity.y += 0.1f;

				rbd[i].image->setPosition(rbd[i].image->getPosition() + rbd[i].velocity);
			//	rbd[i].offset = sf::Vector2f(0, 0);
			}
		}
	}
	
	for (int i = 0; i < 300; i++)
	{
		// colission calculation
		if (rbd[i].isCreated && !rbd[i].isKinamatic)
		{
			sf::FloatRect imgBox = rbd[i].image->getGlobalBounds();
			sf::Vector2f shiftPos =  sf::Vector2f(imgBox.left - rbd[i].velocity.x , imgBox.top - rbd[i].velocity.y);
			rbd[i].isHit = false;
			offset = sf::Vector2f(0,0);
			actionNormal = sf::Vector2f(0, 0);

			for (int j = 0; j < 300; j++)
			{
				if (i != j && rbd[j].isCreated)
				{
					sf::FloatRect b1 = rbd[i].image->getGlobalBounds();
					sf::FloatRect b2 = rbd[j].image->getGlobalBounds();

					bool t11 = b1.top < b2.top + b2.height;
					bool t12 = b1.top + b1.height > b2.top;
					bool l11 = b1.left < b2.left + b2.width;
					bool l12 = b1.left + b1.width > b2.left;

					if (t11 && t12 && l11 && l12) {
						rbd[i].isHit = true;

						sf::FloatRect imgBoxOther = rbd[j].image->getGlobalBounds();
						sf::Vector2f shiftPosOther = sf::Vector2f(imgBoxOther.left - rbd[j].velocity.x, imgBoxOther.top - rbd[j].velocity.y);

					

						bool t21 = shiftPos.y < shiftPosOther.y + b2.height;
						bool t22 = shiftPos.y + b1.height > shiftPosOther.y;
						bool l21 = shiftPos.x < shiftPosOther.x + b2.width;
						bool l22 = shiftPos.x + b1.width > shiftPosOther.x;

						float totalH = b1.height + b2.height + 1;
						float totalW = b1.width + b2.width + 1;

						bool solved = false;

						// top hit
						if (t11 != t21)
						{
							std::cout << "hit at top" << std::endl;
							actionNormal.y += 1;
							offset.y += totalH - (b1.top + b1.height - b2.top);
							solved = true;
						}

						// bottom hit
						if (t12 != t22)
						{
							std::cout << "hit at bottom" << std::endl;
							actionNormal.y += -1;
							offset.y += (b2.top + b2.height - b1.top) - totalH;
							solved = true;
						}

						// left hit
						if (l11 != l21)
						{
							std::cout << "hit at left" << std::endl;
							actionNormal.x += 1;
							offset.x += totalW - (b1.left + b1.width - b2.left);
							solved = true;
						}

						// right hit
						if (l12 != l22)
						{
							std::cout << "hit at right" << std::endl;
							actionNormal.x += -1;
							offset.x += (b2.left + b2.width - b1.left) - totalW;
							solved = true;
						}

					/*
					if (t11 && t12 && l11 && l12) {
						rbd[i].isHit = true;

						bool t21 = shiftPos.y < b2.top + b2.height;
						bool t22 = shiftPos.y + b1.height > b2.top;
						bool l21 = shiftPos.x < b2.left + b2.width;
						bool l22 = shiftPos.x + b1.width > b2.left;

						float totalH = b1.height + b2.height + 1;
						float totalW = b1.width + b2.width + 1;

						bool solved = false;
						
						// top hit
						if (t11 != t21)
						{
							std::cout << "hit at top" << std::endl;
							actionNormal.y += 1;
							offset.y += totalH - (b1.top + b1.height - b2.top);
							solved = true;
						}

						// bottom hit
						if (t12 != t22)
						{
							std::cout << "hit at bottom" << std::endl;
							actionNormal.y += -1;
							offset.y += (b2.top + b2.height - b1.top) - totalH;
							solved = true;
						}

						// left hit
						if (l11 != l21)
						{
							std::cout << "hit at left" << std::endl;
							actionNormal.x += 1;
							offset.x += totalW - (b1.left + b1.width - b2.left);
							solved = true;
						}

						// right hit
						if (l12 != l22)
						{
							std::cout << "hit at right" << std::endl;
							actionNormal.x += -1;
							offset.x += (b2.left + b2.width - b1.left) - totalW;
							solved = true;
						}
						
						if (!solved)

						{
							float v1 = b1.top - (b2.top + b2.height);
							float v2 = b2.top - (b1.top + b1.height);

							float h1 = b1.left - (b2.left + b2.width);
							float h2 = b2.left - (b1.left + b1.width);

							float vDif = v1 > v2 ? v1 : v2;
							float hDif = h1 > h2 ? h1 : h2;

							float cornerLim = vDif + hDif;

							if (cornerLim < -10)
							{
								if (vDif > hDif) {

									// hit top
									if (v1 > v2)
									{
										actionNormal.y += 1;
										offset.y += -v1;
									}
									// hit bottom
									else
									{
										actionNormal.y += -1;
										offset.y += v2;
									}
								}

								else {
									// hit left
									if (h1 > h2)
									{
										actionNormal.x += 1;
										offset.x += -h1;
									}
									// hit right
									else
									{
										actionNormal.x += -1;
										offset.x += h2;
									}
								}
							}

							else
							{
								// hit top
								if (v1 > v2)
								{
									actionNormal.y += 1;
									offset.y += -v1;
								}
								// hit bottom
								else
								{
									actionNormal.y += -1;
									offset.y += v2;
								}

								// hit left
								if (h1 > h2)
								{
									actionNormal.x += 1;
									offset.x += -h1;
								}
								// hit right
								else
								{
									actionNormal.x += -1;
									offset.x += h2;
								}
							}
						}*/
					}
				}
			}
			// finding the reflective velocity
			
			if (rbd[i].isHit) {
				sf::Vector2f normalPerf = MyMath::Normalize(actionNormal);
				rbd[i].recVelocity = rbd[i].velocity + (normalPerf * MyMath::Dot(normalPerf, -rbd[i].velocity) * 2.0f);
				rbd[i].offset = offset;
			}
		}
	}

	for (int i = 0; i < 300; i++)
	{
		if (rbd[i].isCreated)
		{
			// static or not
			if (!rbd[i].isKinamatic && rbd[i].isHit)
			{
				// applay rec velocity
				rbd[i].velocity = rbd[i].recVelocity;
				rbd[i].recVelocity = sf::Vector2f(0,0);

				// applay offset
				sf::Vector2f pos = rbd[i].image->getPosition();
				rbd[i].image->setPosition(pos + rbd[i].offset);
				rbd[i].offset = sf::Vector2f(0, 0);

			}
		}
	}

}

/*
bool Engine::AABBCheck(sf::Vector2f lp, sf::FloatRect b1, sf::FloatRect b2)
{
	
	if (b1.top < b2.top + b2.height &&
		b1.top + b1.height > b2.top &&
		b1.left < b2.left + b2.width &&
		b1.left + b1.width > b2.left)

	bool t11 = b1.top < b2.top + b2.height;
	bool t12 = b1.top + b1.height > b2.top;
	bool l11 = b1.left < b2.left + b2.width;
	bool l12 = b1.left + b1.width > b2.left;


	//if (t11 && t12 && l11 && l12){

		bool t21 = lp.y < b2.top + b2.height;
		bool t22 = lp.y + b1.height > b2.top;
		bool l21 = lp.x < b2.left + b2.width;
		bool l22 = lp.x + b1.width > b2.left;
		
		float totalH = b1.height + b2.height + 1;
		float totalW = b1.width + b2.width + 1;

		std::cout << t11 << t12 << l11 << l12 << std::endl;
		std::cout << t21 << t22 << l21 << l22 << std::endl;
	//	std::cout << v1 << v2 << h1 << h2 << std::endl;
		
		bool solved = false;

		// top hit
		if (t11 != t21)
		{
			std::cout << "hit at top" << std::endl;
			actionNormal.y += 1;
			offset.y += totalH - (b1.top + b1.height - b2.top);
			solved = true;
		}

		// bottom hit
		if (t12 != t22) 
		{
			std::cout << "hit at bottom" << std::endl;
			actionNormal.y += -1;
			offset.y += (b2.top + b2.height - b1.top) - totalH;
			solved = true;
		}

		// left hit
		if (l11 != l21)
		{
			std::cout << "hit at left" << std::endl;
			actionNormal.x += 1;
			offset.x += totalW - (b1.left + b1.width - b2.left);
			solved = true;
		}

		// right hit
		if (l12 != l22)
		{
			std::cout << "hit at right" << std::endl;
			actionNormal.x += -1;
			offset.x += (b2.left + b2.width - b1.left) - totalW;
			solved = true;
		}
		
		if (solved) return true;

		float v1 = b1.top - (b2.top + b2.height);
		float v2 = b2.top - (b1.top + b1.height);

		float h1 = b1.left - (b2.left + b2.width);
		float h2 = b2.left - (b1.left + b1.width);

		float vDif = v1 > v2 ? v1 : v2;
		float hDif = h1 > h2 ? h1 : h2;

		float cornerLim = vDif + hDif;

		if (cornerLim < -5)
		{
			if (vDif > hDif) {

				// hit top
				if (v1 > v2)
				{
					actionNormal.y += 1;
					offset.y += -v1;
				}
				// hit bottom
				else
				{
					actionNormal.y += -1;
					offset.y += v2;
				}
			}

			else {
				// hit left
				if (h1 > h2)
				{
					actionNormal.x += 1;
					offset.x += -h1;
				}
				// hit right
				else
				{
					actionNormal.x += -1;
					offset.x += h2;
				}
			}
		}

		else 
		{
			// hit top
			if (v1 > v2)
			{
				actionNormal.y += 1;
				offset.y += -v1;
			}
			// hit bottom
			else
			{
				actionNormal.y += -1;
				offset.y += v2;
			}

			// hit left
			if (h1 > h2)
			{
				actionNormal.x += 1;
				offset.x += -h1;
			}
			// hit right
			else
			{
				actionNormal.x += -1;
				offset.x += h2;
			}
		}

		// find colission normal
		/*
		float v1 = b1.top - (b2.top + b2.height);
		float v2 = b2.top - (b1.top + b1.height);

		float h1 = b1.left - (b2.left + b2.width);
		float h2 = b2.left - (b1.left + b1.width);
		
		
		// last pos conditions
		

		return true;
	}

	return false;

}
*/



Rigidbody* Engine::RegRigidbody()
{

	for (int i = 0; i < 300; i++)
	{
		if (!rbd[i].isCreated)
		{
			rbd[i].isCreated = true;
			return &rbd[i];
			break;
		}
	}
	
}


// Draw section ------------------------------------

sf::Texture* Engine::GetTexture(const std::string& path) 
{
	sf::Vector2u size = texDict[path].getSize();

	if (size.x + size.y > 0)
	{
		return &texDict[path];
	}
	else
	{
		texDict[path] = sf::Texture();
		texDict[path].loadFromFile(path);
		return &texDict[path];
	}
}

void Engine::DrawScene()
{
	for (int i = 0; i < renderCount; i++)
	{
		if (Renderers[i].getTexture() != blankTexture)
		{
			window->draw(Renderers[i]);
		}
	}
}

sf::Sprite* Engine::AddRenderer(std::string path, sf::Vector2f pos)
{
	for (int i = 0; i < renderCount; i++)
	{
		sf::FloatRect size = Renderers[i].getGlobalBounds();
		if (Renderers[i].getTexture() == blankTexture)
		{
			sf::Texture* tex = GetTexture(path);
			Renderers[i].setTexture(*tex, true);
			Renderers[i].setOrigin(sf::Vector2f(tex->getSize().x * 0.5f, tex->getSize().y * 0.5f));
			Renderers[i].setPosition(pos);
			return &Renderers[i];
			break;
		}
	}
}

void Engine::AddGUI(float length, sf::Vector2f dir, sf::Vector2f orig)
{

	for (int i = 0; i < 100; i++)
	{
		sf::FloatRect size = GUILines[i].getGlobalBounds();
		if (size.width + size.width == 0)
		{
			sf::RectangleShape rectangle(sf::Vector2f(length, 2));
			rectangle.setOrigin(sf::Vector2f(0, 1));
			rectangle.setPosition(orig);
			float rangle = std::atan2(dir.x, dir.y);
			rectangle.rotate(rangle * 57.2958f);
			rectangle.setFillColor(sf::Color(0, 255, 0, 128));
			GUILines[i] = rectangle;
			break;
		}
	}

}

void Engine::DrawGUI()
{
	for (int i = 0; i < 100; i++)
	{
		window->draw(GUILines[i]);
	}
	
}

void Engine::Run()
{
	if(!initialized) Init();

	while(window->isOpen())
	{
		sf::Int32 currentTime = clock.getElapsedTime().asMilliseconds();

		// Physics
		if (currentTime >= nextPhysicsTime)
		{
			Program::Instanciate()->Physics();
			Physics();
			nextPhysicsTime = currentTime + (1000 / physicsRate);
		}

		// Draw
		if (currentTime >= nextDrawTime)
		{
			window->clear();

			DrawScene();
			Program::Instanciate()->SceneGUI();
			DrawGUI();
			window->display();
			
			nextDrawTime = currentTime + (1000 / frameRate);
		}

		// input
		while (window->pollEvent(*evnt))
		{
			if (evnt->type == sf::Event::Closed)
			{
				window->close();
			}
		}
		// Program scene
		Program::Instanciate()->RunScenes();
		
	}

}

void Engine::Reset()
{
	// disabling GUI lines
	for (int i = 0; i < 100; i++)
	{
		GUILines[i].setSize(sf::Vector2f(0,0));
	}

	// disabling Render Images
	for (int i = 0; i < renderCount; i++)
	{
		Renderers[i].setTexture(*blankTexture);
	}

	// disabling Render Images
	for (int i = 0; i < 300; i++)
	{
		rbd[i].isCreated = false;
	}
}
