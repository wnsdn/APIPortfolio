#pragma once
#include <map>
#include <list>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineRenderer;
class GameEngineCamera
{
public:
	GameEngineCamera();
	~GameEngineCamera();
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	void InsertRenderer(GameEngineRenderer* _Renderer, bool _Ordered);
	void InsertUIRenderer(GameEngineRenderer* _Renderer, bool _Front);
	void Render(float _Delta);
	void Release();

	float4 GetPos() const
	{
		return Pos;
	}
	void SetRenderPos(const float4& _Pos)
	{
		Pos = _Pos;
	}
	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}
private:
	float4 Pos = {};
	std::map<int, std::list<GameEngineRenderer*>> Ordered_Renderer;
	std::map<int, std::list<GameEngineRenderer*>> Unordered_Renderer;
	std::map<int, std::list<GameEngineRenderer*>> UI_Renderer;
};