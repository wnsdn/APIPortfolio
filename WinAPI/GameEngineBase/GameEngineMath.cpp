#include "GameEngineMath.h"

const float4 float4::Left = { -1.f, 0.f };
const float4 float4::Right = { 1.f, 0.f };
const float4 float4::Up = { 0.f, -1.f };
const float4 float4::Down = { 0.f, 1.f };

const int2 int2::Left = { -1, 0 };
const int2 int2::Right = { 1, 0 };
const int2 int2::Up = { 0, -1 };
const int2 int2::Down = { 0, 1 };
const int2 int2::UpLeft = { -1, -1 };
const int2 int2::UpRight = { 1, -1 };
const int2 int2::DownLeft = { -1, 1 };
const int2 int2::DownRight = { 1, 1 };

int2 float4::ToInt2() const
{
	return { static_cast<int>(X), static_cast<int>(Y) };
}