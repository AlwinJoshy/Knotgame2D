#include "TileFormat.h"
#include "SaveNLoad.h"
#include <iostream>
#include <fstream>



// save tile data
void SaveNLoad::SaveTileFormat(std::string fileName, int tileList[])
{
	std::ofstream fs;
	fs.open(fileName + ".txt");
	TileFormat tileObj(tileList);

	if (fs.is_open())
	{
		fs.write((char*)&tileObj, sizeof(tileObj));
		//fs << "Test Text Here...";
		std::cout << "Data Saved" << std::endl;
		fs.close();
	}
	else
	{
		std::cout << "saving failed" << std::endl;
	}
}

// load tile data
// and return array pointer
TileFormat SaveNLoad::LoadTileFormat(std::string fileName)
{
	TileFormat tileObj;
	std::ifstream fs;
	fs.open(fileName + ".txt");

	fs.read((char*)&tileObj, sizeof(tileObj));

	return tileObj;
}