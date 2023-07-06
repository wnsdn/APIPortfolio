#pragma once
#include <GameEngineBase/GameEngineMath.h>

#define Rgb(r, g, b) r | (g << 8) | (b << 16)

const float4 TileSize = { 42, 42 };

const int IndexLeft = 0;
const int IndexTop = 0;
const int IndexRight = 15;
const int IndexBottom = 13;

const float MapLeft = 21;
const float MapTop = 43;
const float MapRight = MapLeft + TileSize.X * IndexRight;
const float MapBottom = MapTop + TileSize.Y * IndexBottom;

enum class UpdateOrder
{
	Tile,

	Water,
	Block,
	Object,
	Bomb,
	Item,

	Player,
	Monster,
	Boss,

	UI,

	None,
};

enum class RenderOrder
{
	//1
	BackUI = -4,
	BackGround,
	Tile,
	Shadow,

	//2
	InGameObject = 0,
	InGameObjectEnd = 12,

	//3
	FrontUI = 13,
	UI_Button,
	UI_GameResult,
	UI_Curtain,
	UI_Text,
	UI_Cursor,

	//4
	Text,

	//5
	None,
};

int2 PosToIndex(const float4& _Pos);
float4 IndexToPos(const int2& _Index);
