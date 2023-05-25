#pragma once
#include <map>
#include <list>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineCamera
{
public:
	GameEngineCamera();
	~GameEngineCamera();
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	void InsertRenderer(class GameEngineRenderer* _Renderer, bool _Ordered);
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
	std::map<int, std::list<class GameEngineRenderer*>> Ordered_Renderer;
	std::map<int, std::list<class GameEngineRenderer*>> Unordered_Renderer;
};