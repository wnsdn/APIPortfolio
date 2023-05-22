#pragma once
#include <map>
#include <string>

class ResourceManager
{
public:
	static ResourceManager& GetInst()
	{
		static ResourceManager Inst;
		return Inst;
	}

	class GameEngineTexture* LoadTexture(const std::string& _Path);
private:
	std::map<std::string, class GameEngineTexture*> AllTexture;

	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager& _Other) = delete;
	ResourceManager(ResourceManager&& _Other) noexcept = delete;
	ResourceManager& operator=(const ResourceManager& _Other) = delete;
	ResourceManager& operator=(ResourceManager&& _Other) noexcept = delete;
};