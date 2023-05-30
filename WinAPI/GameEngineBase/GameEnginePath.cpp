#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::~GameEnginePath()
{
}

std::filesystem::path GameEnginePath::GetPath(const std::string& _ResourceType, const std::string& _Path)
{
	std::filesystem::path Path = std::filesystem::current_path();

	while (true)
	{
		std::filesystem::path FindPath = Path;
		FindPath.append(_ResourceType);

		if (std::filesystem::exists(FindPath))
		{
			Path = FindPath;
			break;
		}
		else
		{
			Path = Path.parent_path();
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert("Fail to find PATH: " + _Path);
			return std::filesystem::path();
		}
	}

	Path.append(_Path);
	return Path;
}
