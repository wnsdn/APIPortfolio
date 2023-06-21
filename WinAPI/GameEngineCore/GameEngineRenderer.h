#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include "GameEngineSubObject.h"

class GameEngineCamera;
class GameEngineActor;
class GameEngineTexture;
class GameEngineRenderer : public GameEngineObject, public GameEngineSubObject
{
public:
	GameEngineRenderer();
	virtual ~GameEngineRenderer();
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void LoadTexture(const std::string& _Filename, const float4& _Pos, const float4& _Size);
	void CreateTexture(const std::string& _Filename, const float4& _Size, unsigned int _Color);

	void Render(float _Delta) override;
	void TextRender(float _Delta);
	void GaugeRender(float _Delta);

	void SetText(const std::string& _Text, float _Size = 20.0f, float _Outline = 1.0f,
		const std::string& _Face = "Digital-7", int _Color = ((246 | (234 << 8)) | (46 << 16)))
	{
		Text.Str = _Text;
		Text.Size = _Size;
		Text.Face = _Face;
		Text.Outline = _Outline;
		Text.Color = _Color;
	}

	void CreateAnimation(const std::string& _AnimationName,
		int _XFrame, int _YFrame, int _Count, float _Inter, bool _Loop, bool _Reverse = false);
	void ChangeAnimation(const std::string& _AnimationName);

	std::string GetName() const
	{
		return Name;
	}
	void SetName(const std::string& _Name)
	{
		Name = _Name;
	}
	GameEngineCamera* GetCamera() const
	{
		return Camera;
	}
	void SetCamera(GameEngineCamera* const _Camera)
	{
		Camera = _Camera;
	}
	GameEngineActor* GetActor() const
	{
		return Actor;
	}
	void SetActor(GameEngineActor* const _Actor)
	{
		Actor = _Actor;
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

	bool GetAlphaRender() const
	{
		return AlphaRender;
	}
	void SetAlphaRender(const bool _AlphaRender)
	{
		AlphaRender = _AlphaRender;
	}
	unsigned char GetAlphaValue() const
	{
		return AlphaValue;
	}
	void SetAlphaValue(const unsigned char _AlphaValue)
	{
		AlphaValue = _AlphaValue;
	}

	bool IsAnimationEnd(const std::string& _AnimationName);
	void ResetAnimation(const std::string& _AnimationName);

	bool GetIsGauge() const
	{
		return IsGauge;
	}
	void SetIsGauge(const bool _IsGauge)
	{
		IsGauge = _IsGauge;
		Pos -= Scale.Half();
		Pos.X += 1;
		Pos.Y += 1;
	}
	float4 GetAdjPos() const
	{
		return AdjPos;
	}
	void SetAdjPos(const float4& _AdjPos)
	{
		AdjPos = _AdjPos;
	}
	void AddAdjPos(const float4& _AdjPos)
	{
		AdjPos += _AdjPos;
	}
	float4 GetAdjScale() const
	{
		return AdjScale;
	}
	void SetAdjScale(const float4& _AdjScale)
	{
		AdjScale = _AdjScale;
	}
	void AddAdjScale(const float4& _AdjScale)
	{
		AdjScale += _AdjScale;
	}
private:
	std::string Name = "";
	GameEngineCamera* Camera = nullptr;
	GameEngineActor* Actor = nullptr;
	GameEngineTexture* Texture = nullptr;

	float4 CopyPos = {};
	float4 CopyScale = {};
	bool AlphaRender = false;
	unsigned char AlphaValue = 0;

	bool IsGauge = false;
	float4 AdjPos = {};
	float4 AdjScale = {};
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
		bool Reverse = false;
		bool AnimationEnd = false;
	};
	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;
private:
	class tText
	{
	public:
		std::string Str = "";
		std::string Face = "";
		float Size = 0.0f;
		float Outline = 0.0f;
		int Color = 0;
	}Text;
};