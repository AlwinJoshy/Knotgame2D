#pragma once
#include <iostream>
#include "TileFormat.h"
class SaveNLoad
{
public:
	static void SaveTileFormat(std::string fileName, int tileList[]);
	static TileFormat LoadTileFormat(std::string fileName);
};

