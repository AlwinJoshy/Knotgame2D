#pragma once
#include "Engine.h"
#include "Button.h"

class Scene
{
protected :
	
public:
	static Engine* engine;
	int buttonCount;
	Button buttons[10];
	

	virtual void Start();
	virtual void OnGUI();
	virtual void Play();
	virtual void Physics();
	virtual void Close();
};

