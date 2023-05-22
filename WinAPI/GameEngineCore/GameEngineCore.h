#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineCore
{
public:
	template <typename CoreProcessType>
	static void EngineStart(HINSTANCE _Hinst, const std::string& _Title)
	{
		EngineStart(_Hinst, _Title, new CoreProcessType());
	}
private:
	static class GameEngineProcess* Process;

	static void EngineStart(HINSTANCE _Hinst, const std::string& _Title, class GameEngineProcess* _Process);
	static void CoreStart();
	static void CoreUpdate();
	static void CoreEnd();

	GameEngineCore();
	~GameEngineCore();
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;
};