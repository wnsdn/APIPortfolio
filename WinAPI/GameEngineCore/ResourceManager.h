#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineTexture;
class ResourceManager
{
public:
	static ResourceManager& GetInst()
	{
		static ResourceManager Inst;
		return Inst;
	}

	GameEngineTexture* LoadTexture(const std::string& _Filename);
	GameEngineTexture* CreateTexture(const std::string& _Path, const float4& _Scale);
private:
	std::map<std::string, GameEngineTexture*> AllTexture;

	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager& _Other) = delete;
	ResourceManager(ResourceManager&& _Other) noexcept = delete;
	ResourceManager& operator=(const ResourceManager& _Other) = delete;
	ResourceManager& operator=(ResourceManager&& _Other) noexcept = delete;
};