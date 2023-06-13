#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include "GameEngineSubObject.h"

class GameEngineLevel;
class GameEngineRenderer;
class GameEngineActor : public GameEngineObject, public GameEngineSubObject
{
	friend class GameEngineLevel;
public:
	GameEngineActor();
	virtual ~GameEngineActor();
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _Filename, EnumType _RenderOrder, const float4& _Pos = { 0, 0 }, const float4& _Size = { 1, 1 })
	{
		return CreateRenderer(_Filename, static_cast<int>(_RenderOrder), _Pos, _Size);
	}
	GameEngineRenderer* CreateRenderer(const std::string& _Filename, int _RenderOrder, const float4& _Pos, const float4& _Size);
	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _Name, EnumType _RenderOrder, const float4& _Size, unsigned int _Color)
	{
		return CreateRenderer(_Name, static_cast<int>(_RenderOrder), _Size, _Color);
	}
	GameEngineRenderer* CreateRenderer(const std::string& _Name, int _RenderOrder, const float4& _Size, unsigned int _Color);
	GameEngineRenderer* FindRenderer(const std::string& _Filename);

	GameEngineLevel* GetLevel() const
	{
		return Level;
	}
	void SetLevel(GameEngineLevel* const _Level)
	{
		Level = _Level;
	}
	int2 GetIndex() const
	{
		return Index;
	}
	void SetIndex(const int2& _Index)
	{
		Index = _Index;
	}
protected:
	GameEngineLevel* Level = nullptr;
	int2 Index = {};

	std::map<std::string, GameEngineRenderer*> AllRenderer;
};