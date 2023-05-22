#pragma once
#include <string>

class GameEngineString
{
public:
	static std::string ToUpperReturn(const std::string& _Str);
private:
	GameEngineString();
	~GameEngineString();
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};