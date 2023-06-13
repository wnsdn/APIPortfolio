#include "ResourceManager.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineTexture.h>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto& Pair : AllTexture)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
}

GameEngineTexture* ResourceManager::LoadTexture(const std::string& _Filename)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	auto FindIter = AllTexture.find(Upper);

	if (FindIter != AllTexture.end())
	{
		return FindIter->second;
	}

	GameEngineTexture* NewTexture = new GameEngineTexture();
	NewTexture->ResLoad(GameEnginePath::FilenameToPath(_Filename));
	AllTexture.emplace(Upper, NewTexture);

	return NewTexture;
}

GameEngineTexture* ResourceManager::CreateTexture(const std::string& _Name, const float4& _Scale)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	auto FindIter = AllTexture.find(Upper);

	if (FindIter != AllTexture.end())
	{
		return FindIter->second;
	}

	GameEngineTexture* NewTexture = new GameEngineTexture();
	NewTexture->ResCreate(_Scale);
	AllTexture.emplace(Upper, NewTexture);

	return NewTexture;
}
