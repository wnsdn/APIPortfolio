#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineGraphics
{
public:
	GameEngineGraphics();
	~GameEngineGraphics();
	GameEngineGraphics(const GameEngineGraphics& _Other) = delete;
	GameEngineGraphics(GameEngineGraphics&& _Other) noexcept = delete;
	GameEngineGraphics& operator=(const GameEngineGraphics& _Other) = delete;
	GameEngineGraphics& operator=(GameEngineGraphics&& _Other) noexcept = delete;

	static void Init();
	static void Release();

	static void DrawGPText(HDC _ImageDC, const std::string& _Text,
		const std::string _Face, float _Size, const int2& _Pos, float _Outline, int _RGB);
private:
	static Gdiplus::GdiplusStartupInput GSI;
	static ULONG_PTR GToken;
};