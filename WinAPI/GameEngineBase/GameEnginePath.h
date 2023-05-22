#pragma once
#include <filesystem>

class GameEnginePath
{
public:
	static std::filesystem::path GetPath(const std::string& _Path);
private:
	static const std::string TexturePath;

	GameEnginePath();
	~GameEnginePath();
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;
};