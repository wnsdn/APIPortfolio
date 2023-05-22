#include "GameEngineRandom.h"
#include <iostream>

int GameEngineRandom::Seed = 0;

GameEngineRandom::GameEngineRandom()
{
}

GameEngineRandom::~GameEngineRandom()
{
}

void GameEngineRandom::Init()
{
	Seed = (int)time(nullptr);
	srand(Seed);
}

int GameEngineRandom::RandomInt(int _Max, int _Min)
{
	return rand() % (_Max + _Min - 1) + _Min;
}
