#pragma once
#include <GameEngineBase/GameEngineMath.h>

const float4 TileSize = { 42, 42 };

const int IndexLeft = 0;
const int IndexTop = 0;
const int IndexRight = 15;
const int IndexBottom = 13;

const float MapLeft = 21;
const float MapTop = 43;
const float MapRight = MapLeft + TileSize.X * IndexRight;
const float MapBottom = MapTop + TileSize.Y * IndexBottom;

const float TrimRatio = 0.6f;
const float SpeedRatio = 0.8f;

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

	UI,

	None,
};

enum class ZOrder
{
	//1
	BackUI = -3,
	BackGround,
	Tile,

	//2
	InGameObject = 0,
	InGameObjectEnd = 12,
	//3
	FrontUI = 13,
	UI_Button,
	UI_GameResult,
	UI_Curtain,
	UI_GameStart,
	UI_Cursor,

	//4
	None,
};

enum class RenderOrder
{
	Water,
	Block,
	Object,
	Bomb,
	Item,
	Player,
	Monster,

	None,
};

int2 PosToIndex(const float4& _Pos);
float4 IndexToPos(const int2& _Index);
