#pragma once
#include <GameEngineBase/GameEngineMath.h>

class GameEngineSubObject
{
public:
	GameEngineSubObject();
	~GameEngineSubObject();
	GameEngineSubObject(const GameEngineSubObject& _Other) = delete;
	GameEngineSubObject(GameEngineSubObject&& _Other) noexcept = delete;
	GameEngineSubObject& operator=(const GameEngineSubObject& _Other) = delete;
	GameEngineSubObject& operator=(GameEngineSubObject&& _Other) noexcept = delete;

	float4 GetPos() const
	{
		return Pos;
	}
	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}
	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}
	float4 GetScale() const
	{
		return Scale;
	}
	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}
	void AddScale(const float4& _Scale)
	{
		Scale += _Scale;
	}

	float Left() const
	{
		return Pos.X - Scale.hX();
	}
	float Right() const
	{
		return Pos.X + Scale.hX();
	}
	float Top() const
	{
		return Pos.Y - Scale.hY();
	}
	float Bottom() const
	{
		return Pos.Y + Scale.hY();
	}

	int iLeft() const
	{
		return static_cast<int>(Left());
	}
	int iRight() const
	{
		return static_cast<int>(Right());
	}
	int iTop() const
	{
		return static_cast<int>(Top());
	}
	int iBottom() const
	{
		return static_cast<int>(Bottom());
	}
protected:
	float4 Pos = {};
	float4 Scale = {};
};