#include "GameEngineTexture.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

#pragma comment(lib, "msimg32.lib")

GameEngineTexture::GameEngineTexture()
{
}

GameEngineTexture::~GameEngineTexture()
{
}

void GameEngineTexture::ResLoad(const std::string& _Path)
{
	Hbmp = static_cast<HBITMAP>(
		LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (!Hbmp)
	{
		MsgBoxAssert("HBITMAP == nullptr, " + _Path);
	}

	ImageDC = CreateCompatibleDC(nullptr);
	SelectObject(ImageDC, Hbmp);
	GetObjectA(Hbmp, sizeof(BITMAP), &Info);
}

void GameEngineTexture::ResCreate(const float4& _Scale)
{
	Hbmp = CreateCompatibleBitmap(GameEngineWindow::GetInst().GetHDC(), _Scale.iX(), _Scale.iY());

	if (!Hbmp)
	{
		MsgBoxAssert("Fail to CreateCompatibleBitmap, WindowDC");
	}

	ImageDC = CreateCompatibleDC(nullptr);
	SelectObject(ImageDC, Hbmp);
	GetObjectA(Hbmp, sizeof(BITMAP), &Info);
}

void GameEngineTexture::BitCopy(GameEngineTexture* _CopyTexture, const float4& _Pos)
{
	BitBlt(ImageDC,
		_Pos.iX() - _CopyTexture->GetScale().ihX(),
		_Pos.iY() - _CopyTexture->GetScale().ihY(),
		_CopyTexture->GetScale().iX(),
		_CopyTexture->GetScale().iY(),
		_CopyTexture->GetImageDC(),
		0, 0, SRCCOPY);
}

void GameEngineTexture::TransCopy(GameEngineTexture* _CopyTexture,
	const float4& _Pos, const float4& _Scale, 
	const float4& _OtherPos, const float4& _OtherScale)
{
	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		_CopyTexture->GetImageDC(),
		_OtherPos.iX(),
		_OtherPos.iY(),
		_OtherScale.iX(),
		_OtherScale.iY(),
		RGB(255, 0, 255));
}

void GameEngineTexture::StretchCopy(GameEngineTexture* _CopyTexture, 
	const float4& _Pos, const float4& _Scale, 
	const float4& _OtherPos, const float4& _OtherScale)
{
	StretchBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		_CopyTexture->GetImageDC(),
		_OtherPos.iX(),
		_OtherPos.iY(),
		_OtherScale.iX(),
		_OtherScale.iY(),
		SRCCOPY);
}
