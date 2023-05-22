#include "GameEnginePath.h"
#include "GameEngineDebug.h"

const std::string GameEnginePath::TexturePath = "Texture";

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::~GameEnginePath()
{
}

std::filesystem::path GameEnginePath::GetPath(const std::string& _Path)
{
	std::filesystem::path Path = std::filesystem::current_path();

	while (true)
	{
		std::filesystem::path FindPath = Path;
		FindPath.append(TexturePath);

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
		}
	}

	Path.append(_Path);
	return Path;
}
