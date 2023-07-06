#pragma once
#include <vector>
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

	template<typename RenderOrder>
	GameEngineRenderer* CreateRenderer(const std::string& _Filename, RenderOrder _RenderOrder, const float4& _Pos = { 0, 0 }, const float4& _Size = { 1, 1 }, const std::string& _Name = "")
	{
		return CreateRenderer(_Filename, static_cast<int>(_RenderOrder), _Pos, _Size, _Name);
	}
	GameEngineRenderer* CreateRenderer(const std::string& _Filename, int _RenderOrder, const float4& _Pos, const float4& _Size, const std::string& _Name);

	template<typename RenderOrder>
	GameEngineRenderer* CreateRenderer(const std::string& _Name, RenderOrder _RenderOrder, const float4& _Size, unsigned int _Color)
	{
		return CreateRenderer(_Name, static_cast<int>(_RenderOrder), _Size, _Color);
	}
	GameEngineRenderer* CreateRenderer(const std::string& _Name, int _RenderOrder, const float4& _Size, unsigned int _Color);

	template<typename RenderOrder>
	GameEngineRenderer* CreateTextRenderer(const std::string& _Text, RenderOrder _RenderOrder)
	{
		return CreateTextRenderer(_Text, static_cast<int>(_RenderOrder));
	}
	GameEngineRenderer* CreateTextRenderer(const std::string& _Text, int _RenderOrder);
	GameEngineRenderer* FindRenderer(const std::string& _Filename);
	void InsertRenderer();
	void InsertRenderer(const std::string& _Name);

	void DrawRect(const float4& _Pos, const float4& _Scale, unsigned int _Color);
	void DrawLine(const float4& _StartPos, const float4& _EndPos);

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

	std::vector<GameEngineRenderer*> AllRenderer;
};