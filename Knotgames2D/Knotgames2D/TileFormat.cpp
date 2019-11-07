#include "TileFormat.h"

TileFormat::TileFormat()
{

}

TileFormat::TileFormat(int tilesIn[])
{
	Rec(tilesIn);
}

void TileFormat::Rec(int tilesIn[])
{
	for (int i = 0; i < 108; i++)
	{
		tiles[i] = tilesIn[i];
	}
}