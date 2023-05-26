#include "GameEngineString.h"

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

std::string GameEngineString::ToUpperReturn(const std::string& _Str)
{
	std::string Upper = _Str;

	for (auto& Ch : Upper)
	{
		Ch = toupper(Ch);
	}

	return Upper;
}

std::wstring GameEngineString::AnsiToUnicode(const std::string& _Text)
{
	return std::wstring();
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring& _Text)
{
	return std::string();
}

std::string GameEngineString::AnsiToUTF8(const std::string& _Text)
{
	std::wstring Unicode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(Unicode);
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring& _Text)
{
	return std::string();
}
