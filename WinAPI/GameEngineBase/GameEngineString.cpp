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
