#include <iostream>
#include "Program.h"
#include "Engine.h"
#include "Scene.h"
#include "Editor.h"
#include "MainMenu.h"
#include "PlayLevel.h"


int Program::sceneID = 0;
Program* Program::instance = NULL;

Program* Program::Instanciate() 
{
	if (instance == nullptr) 
	{
		instance = new Program();
	}
	return instance;
}

void Program::Initialize()
{
//	Scene* ed = 
	// ed->Start();
	allScenes[0] = new MainMenu();
	allScenes[1] = new Editor();
	allScenes[2] = new PlayLevel();

	allScenes[sceneID]->Start();
//	Engine::Instanciate()->Reset();
//	ShiftScene(0);
	// Initialize the program
}

void Program::ShiftScene(int newSceneID)
{
	allScenes[sceneID]->Close();
	Engine::Instanciate()->Reset();
	sceneID = newSceneID;
	allScenes[sceneID]->Start();
	
}


void Program::Run()
{
	// Initialize Program
	Initialize();
	// Starts the Engine
	Engine::Instanciate()->Run();
}

void Program::RunScenes()
{
	allScenes[sceneID]->Play();
}

void Program::Physics()
{
	allScenes[sceneID]->Physics();
}

void Program::SceneGUI()
{
	allScenes[sceneID]->OnGUI();
}