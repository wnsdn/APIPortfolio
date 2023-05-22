#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

class GameEngineRenderer : public GameEngineObject
{
public:
	GameEngineRenderer();
	virtual ~GameEngineRenderer();
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Path, class GameEngineActor* _Master, const float4& _Pos, const float4& _Size);
	void Render(class GameEngineCamera* _Camera, float _Delta);

	void CreateAnimation(const std::string& _AnimationName,
		int _XFrame, int _YFrame, int _Count, float _Inter, bool _Loop);
	void ChangeAnimation(const std::string& _AnimationName);

	GameEngineActor* GetMaster() const
	{
		return Master;
	}

	float4 GetRenderPos() const
	{
		return RenderPos;
	}
	void SetRenderPos(const float4& _RenderPos)
	{
		RenderPos = _RenderPos;
	}
	float4 GetRenderScale() const
	{
		return RenderScale;
	}
	void SetRenderScale(const float4& _RenderScale)
	{
		RenderScale = _RenderScale;
	}
	float4 GetCopyPos() const
	{
		return CopyPos;
	}
	void SetCopyPos(const float4& _CopyPos)
	{
		CopyPos = _CopyPos;
	}
	float4 GetCopyScale() const
	{
		return CopyScale;
	}
	void SetCopyScale(const float4& _CopyScale)
	{
		CopyScale = _CopyScale;
	}
private:
	class Animation
	{
	public:
		int CurFrame = 0;
		int StartFrame = 0;
		int EndFrame = 0;
		int YFrame = 0;
		float CurInter = 0.f;
		float Inter = 0.1f;
		bool Loop = true;
	};

	class GameEngineActor* Master = nullptr;
	class GameEngineTexture* Texture = nullptr;

	float4 RenderPos = {};
	float4 RenderScale = {};
	float4 CopyPos = {};
	float4 CopyScale = {};

	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;
};