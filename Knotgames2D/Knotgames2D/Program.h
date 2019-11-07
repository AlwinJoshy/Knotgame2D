#pragma once
#include "Scene.h"


class Program
{
private:
	static Program* instance;
	Scene* allScenes[10];

public:
	static int sceneID;
	static Program* Instanciate();

	void Initialize();

	void RunScenes();

	void Physics();

	void SceneGUI();

	void Run();

	void ShiftScene(int newSceneID);

};

