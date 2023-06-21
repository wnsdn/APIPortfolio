#pragma once
#include <GameEngineBase/GameEngineMath.h>

#define Rgb(R, G, B) R | (G << 8) | (B << 16)

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

enum class RenderOrder
{
	Tile,
	Block,
	Object,
	Item,
	Position,

	UI,
	Text,

	None,
};

float4 PosToIndexPos(const float4& _Pos, const float4& _LeftTop, const float4& _Size);
int2 PosToIndex(const float4& _Pos, const float4& _LeftTop, const float4& _Size);