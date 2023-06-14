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
	void SetText(const std::string& _Text, int _TextScale = 20,
		const std::string& _Face = "±¼¸²")
	{
		Text = _Text;
		TextScale = _TextScale;
		Face = _Face;
	}

	void CreateAnimation(const std::string& _AnimationName,
		int _XFrame, int _YFrame, int _Count, float _Inter, bool _Loop, bool _Reverse = false);
	void ChangeAnimation(const std::string& _AnimationName);

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

	bool IsCurAnimationEnd()
	{
		if (!CurAnimation)
		{
			return false;
		}

		int Count = CurAnimation->EndFrame - CurAnimation->StartFrame + 1;
		if (!CurAnimation->AnimationEnd && LiveTime >= static_cast<float>(Count) * CurAnimation->Inter)
		{
			CurAnimation->AnimationEnd = true;
			LiveTime = 0.0f;
		}

		return CurAnimation->AnimationEnd;
	}
	void ResetCurAnimation()
	{
		if (!CurAnimation || CurAnimation->Loop)
		{
			return;
		}

		CurAnimation->CurFrame = CurAnimation->StartFrame;
		CurAnimation->AnimationEnd = false;
	}
private:
	GameEngineCamera* Camera = nullptr;
	GameEngineActor* Actor = nullptr;
	GameEngineTexture* Texture = nullptr;

	float4 CopyPos = {};
	float4 CopyScale = {};
	bool AlphaRender = false;
	unsigned char AlphaValue = 0;
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
	std::string Text = "";
	int TextScale = 0;
	std::string Face = "";
};