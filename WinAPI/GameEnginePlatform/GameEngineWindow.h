#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineTexture.h"

class GameEngineWindow
{
public:
	static GameEngineWindow& GetInst()
	{
		static GameEngineWindow Inst;
		return Inst;
	}

	void Open(HINSTANCE _Hinst, const std::string& _Title);
	void MessageLoop(void(*_Start)(), void(*_Update)(), void(*_End)());

	void SetPosAndScale(const float4& _Pos, const float4& _WindowScale);
	void ClearBackBuffer();
	void DoubleBuffering();

	HDC GetHDC()
	{
		return Hdc;
	}
	float4 GetScale()
	{
		return Scale;
	}
	GameEngineTexture* GetBackBuffer()
	{
		return BackBuffer;
	}
	bool IsFocus() const
	{
		return IsFocusValue;
	}
	float4 GetMousePos();
private:
	HINSTANCE Hinst = nullptr;
	HWND Hwnd = nullptr;
	HDC Hdc = nullptr;
	std::string Title = "";
	float4 Scale = {};
	GameEngineTexture* BackBuffer = nullptr;

	static bool IsWindowUpdate;
	static bool IsFocusValue;

	static LRESULT CALLBACK WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp);

	GameEngineWindow();
	~GameEngineWindow();
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;
};