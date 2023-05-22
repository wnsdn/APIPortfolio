#pragma once
#include <Windows.h>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineTexture
{
public:
	GameEngineTexture();
	~GameEngineTexture();
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);
	void ResCreate(const float4& _Scale);

	void BitCopy(GameEngineTexture* _CopyTexture, const float4& _Pos);
	void TransCopy(GameEngineTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale);
	void StretchCopy(GameEngineTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale);

	HDC GetImageDC() const
	{
		return ImageDC;
	}
	void SetImageDC(HDC _ImageDC)
	{
		ImageDC = _ImageDC;
	}
	float4 GetScale()
	{
		return { static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}
private:
	HDC ImageDC = nullptr;
	HBITMAP Hbmp = nullptr;
	BITMAP Info = {};
};