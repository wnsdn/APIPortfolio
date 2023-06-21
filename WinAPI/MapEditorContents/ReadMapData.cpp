#include "ReadMapData.h"
#include <fstream>
#include <sstream>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Tile.h"

ReadMapData::ReadMapData(const std::string& _Filename)
{
	std::ifstream IFS(_Filename);
	std::string MapData{};
	std::vector<std::string> TileData{};
	std::vector<std::string> AttrData{};

	if (IFS)
	{
		std::getline(IFS, MapData, static_cast<char>(26));

		SplitMapData(MapData, TileData);
		SplitTileData(TileData, AttrData);
		SplitAttrData(AttrData);

		IFS.close();
	}
}

ReadMapData::~ReadMapData()
{
}

void ReadMapData::SplitMapData(const std::string& _MapData, std::vector<std::string>& _TileData)
{
	std::stringstream Ss(_MapData);
	std::string Str{};

	while (std::getline(Ss, Str, '\n'))
	{
		_TileData.emplace_back(Str);
	}
}

void ReadMapData::SplitTileData(const std::vector<std::string>& _TileData, std::vector<std::string>& _AttrData)
{
	int Size = static_cast<int>(_TileData.size());

	for (int i = 0; i < Size; ++i)
	{
		std::stringstream Ss(_TileData[i]);
		std::string Str{};

		while (std::getline(Ss, Str, ' '))
		{
			_AttrData.emplace_back(Str);
		}
	}
}

void ReadMapData::SplitAttrData(const std::vector<std::string>& _AttrData)
{
	for (int y = 0; y < 13; ++y)
	{
		for (int x = 0; x < 15; ++x)
		{
			Tile* TilePtr = Tile::TileArr[y][x];
			for (int i = 0; i < 5; ++i)
			{
				if (_AttrData[y * 15 * 5 + x * 5 + i] == "0")
				{
					TilePtr->Attr[i].Idx = { 0,0 };
					TilePtr->Attr[i].IsSet = false;
					TilePtr->Renderer[i]->Off();
				}
				else
				{
					TilePtr->Attr[i].Idx.X = static_cast<int>(_AttrData[y * 15 * 5 + x * 5 + i][0] - '0');
					TilePtr->Attr[i].Idx.Y = static_cast<int>(_AttrData[y * 15 * 5 + x * 5 + i][2] - '0');
					TilePtr->Attr[i].IsSet = true;
					TilePtr->Renderer[i]->On();
				}
			}
		}
	}
}
