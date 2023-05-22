#pragma once

class GameEngineRandom
{
public:
	static void Init();
	static int RandomInt(int _Max, int _Min = 1);
private:
	static int Seed;

	GameEngineRandom();
	~GameEngineRandom();
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;
};