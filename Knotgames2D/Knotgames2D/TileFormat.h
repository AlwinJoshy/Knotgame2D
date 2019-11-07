#pragma once
class TileFormat
{
public:
	int tiles[108];
	TileFormat();
	TileFormat(int tilesIn[]);
	void Rec(int tilesIn[]);
};

