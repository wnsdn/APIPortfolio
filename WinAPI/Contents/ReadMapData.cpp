#include "ReadMapData.h"
#include <fstream>
#include <sstream>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"
#include "Block.h"
#include "Object.h"
#include "Item.h"
#include "Player.h"
#include "Monster.h"

ReadMapData::ReadMapData(const std::string& _Filename, GameEngineLevel* _Level)
{
	Level = _Level;

	std::ifstream IFS(GameEnginePath::FilenameToPath(_Filename));
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
	std::vector<int2> VecInt2;
	for (int y = 0; y < 13; ++y)
	{
		for (int x = 0; x < 15; ++x)
		{
			for (int i = 0; i < 5; ++i)
			{
				if (_AttrData[y * 15 * 5 + x * 5 + i] != "0")
				{
					float TypeX = static_cast<float>(_AttrData[y * 15 * 5 + x * 5 + i][0] - '0');
					float TypeY = static_cast<float>(_AttrData[y * 15 * 5 + x * 5 + i][2] - '0');
					switch (i)
					{
					case 0:
						Level->CreateActor<Tile>(UpdateOrder::Tile)
							->Init({ x,y }, { TypeX, TypeY });
						break;
					case 1:
						Level->CreateActor<Block>(UpdateOrder::Block)
							->Init({ x,y }, { TypeX, TypeY });
						break;
					case 2:
						Level->CreateActor<Object>(UpdateOrder::Object)
							->Init({ x,y }, { TypeX, TypeY });
						break;
					case 3:
						Level->CreateActor<Item>(UpdateOrder::Item)
							->Init({ x,y }, { TypeX, TypeY });
						break;
					case 4:
						if (TypeX == 0)
						{
							VecInt2.emplace_back(x, y);
						}
						else if (TypeX == 1)
						{
							Level->CreateActor<Monster>(UpdateOrder::Monster)
								->Init({ x,y }, "Octopus1.bmp");
						}
						else if (TypeX == 2)
						{
							Level->CreateActor<Monster>(UpdateOrder::Monster)
								->Init({ x,y }, "Octopus2.bmp");
						}
						break;
					}
				}
			}
		}
	}

	int RndInt = GameEngineRandom::RandomInt(4);
	Player::MainPlayer = Level->CreateActor<Player>(UpdateOrder::Player);
	Player::MainPlayer->Init(VecInt2[RndInt - 1], "Bazzi.bmp");
	//Player::MainPlayer->Init(VecInt2[0], "Bazzi.bmp");
}
