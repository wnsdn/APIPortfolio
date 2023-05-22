#include "GameEngineTime.h"

LARGE_INTEGER GameEngineTime::Count = {};
LARGE_INTEGER GameEngineTime::Prev = {};
LARGE_INTEGER GameEngineTime::Cur = {};
double GameEngineTime::DoubleDelta = 0.f;
float GameEngineTime::FloatDelta = 0.f;

GameEngineTime::GameEngineTime()
{
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Init()
{
	QueryPerformanceFrequency(&Count);
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur);
	DoubleDelta = static_cast<double>(Cur.QuadPart - Prev.QuadPart)
		/ static_cast<double>(Count.QuadPart);
	FloatDelta = static_cast<float>(DoubleDelta);
	Prev = Cur;
}
