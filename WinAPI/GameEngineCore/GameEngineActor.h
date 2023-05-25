#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

class GameEngineRenderer;
class GameEngineActor : public GameEngineObject
{
	friend class GameEngineLevel;
public:
	GameEngineActor();
	virtual ~GameEngineActor();
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	template <typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _Path, const std::string& _Name, EnumType _Order, bool _Ordered, const float4 _Pos = { 0, 0 }, const float4 _Size = { 1, 1 })
	{
		return CreateRenderer(_Path, _Name, static_cast<int>(_Order), _Ordered, _Pos, _Size);
	}
	GameEngineRenderer* CreateRenderer(const std::string& _Path, const std::string& _Name, int _Order, bool _Ordered, const float4 _Pos, const float4 _Size);
	GameEngineRenderer* FindRenderer(const std::string& _Name);

	void DrawRect(const float4& _Pos, const float4& _Scale);
	void DrawStr(const float4& _Pos, const char* _Str);

	class GameEngineLevel* GetLevel() const
	{
		return Level;
	}
	void SetLevel(class GameEngineLevel* const _Level)
	{
		Level = _Level;
	}
	float4 GetPos() const
	{
		return Pos;
	}
	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}
	float4 GetScale() const
	{
		return Scale;
	}
	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}
	int2 GetIndex() const
	{
		return Index;
	}
	void SetIndex(const int2& _Index)
	{
		Index = _Index;
	}

	float Left()
	{
		return Pos.X - Scale.hX();
	}
	float Right()
	{
		return Pos.X + Scale.hX();
	}
	float Top()
	{
		return Pos.Y - Scale.hY();
	}
	float Bot()
	{
		return Pos.Y + Scale.hY();
	}

	int iLeft()
	{
		return static_cast<int>(Left());
	}
	int iRight()
	{
		return static_cast<int>(Right());
	}
	int iTop()
	{
		return static_cast<int>(Top());
	}
	int iBot()
	{
		return static_cast<int>(Bot());
	}
protected:
	class GameEngineLevel* Level = nullptr;
	float4 Pos = {};
	float4 Scale = {};
	int2 Index = {};

	std::map<std::string, GameEngineRenderer*> AllRenderer;
};