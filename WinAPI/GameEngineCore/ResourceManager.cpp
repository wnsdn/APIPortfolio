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

GameEngineTexture* ResourceManager::LoadTexture(const std::string& _Path)
{
	std::string Path = GameEnginePath::GetPath(_Path + ".bmp").string();
	std::string Filename = GameEnginePath::GetPath(_Path + ".bmp").filename().string();

	std::string Upper = GameEngineString::ToUpperReturn(Filename);
	auto FindIter = AllTexture.find(Upper);

	if (FindIter != AllTexture.end())
	{
		return FindIter->second;
	}

	GameEngineTexture* NewTexture = new GameEngineTexture();
	NewTexture->ResLoad(Path);
	AllTexture.emplace(std::make_pair(Upper, NewTexture));

	return NewTexture;
}
