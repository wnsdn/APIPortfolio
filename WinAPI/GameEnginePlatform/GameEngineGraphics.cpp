#include "GameEngineGraphics.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "gdiplus")

Gdiplus::GdiplusStartupInput GameEngineGraphics::GSI{};
ULONG_PTR GameEngineGraphics::GToken = 0;

GameEngineGraphics::GameEngineGraphics()
{
}

GameEngineGraphics::~GameEngineGraphics()
{
}

void GameEngineGraphics::Init()
{
	if (Gdiplus::GdiplusStartup(&GToken, &GSI, nullptr) != Gdiplus::Ok)
	{
		MsgBoxAssert("GameEngineGraphics::Init()");
		return;
	}
}

void GameEngineGraphics::Release()
{
	Gdiplus::GdiplusShutdown(GToken);
}

void GameEngineGraphics::DrawGPText(HDC _ImageDC, const std::string& _Text,
	const std::string _Face, float _Size, const int2& _Pos, float _Outline, int _RGB)
{
	Gdiplus::Graphics NewGraphics(_ImageDC);
	NewGraphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	NewGraphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

	std::wstring Text = GameEngineString::AnsiToUnicode(_Text);
	std::wstring Face = GameEngineString::AnsiToUnicode(_Face);
	Gdiplus::FontFamily FontFamily(Face.c_str());
	Gdiplus::StringFormat StrFormat;
	Gdiplus::Point Pt(_Pos.X, _Pos.Y);

	Gdiplus::GraphicsPath GPath;
	GPath.AddString(Text.c_str(), static_cast<int>(Text.size()), &FontFamily,
		Gdiplus::FontStyleRegular, _Size, Pt, &StrFormat);

	Gdiplus::Pen Pen(Gdiplus::Color(0, 0, 0), _Outline);
	Pen.SetLineJoin(Gdiplus::LineJoinRound);

	unsigned char R = _RGB & 255;
	unsigned char G = _RGB >> 8 & 255;
	unsigned char B = _RGB >> 16 & 255;
	Gdiplus::SolidBrush Brush(Gdiplus::Color(R, G, B));

	NewGraphics.DrawPath(&Pen, &GPath);
	NewGraphics.FillPath(&Brush, &GPath);
}
