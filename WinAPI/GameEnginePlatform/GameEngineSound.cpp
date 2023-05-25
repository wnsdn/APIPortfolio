#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

FMOD::System* SoundSystem = nullptr;

class SoundSystemCreater
{
public:
	SoundSystemCreater()
	{
		if (FMOD::System_Create(&SoundSystem) != FMOD_RESULT::FMOD_OK)
		{
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
		}

		if (SoundSystem->init(32, FMOD_DEFAULT, nullptr) != FMOD_RESULT::FMOD_OK)
		{
			MsgBoxAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
		}
	}
	
	~SoundSystemCreater()
	{
		SoundSystem->release();
	}
};
SoundSystemCreater InitInstance = SoundSystemCreater();

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
}

void GameEngineSound::SoundLoad(const std::string& _Name, const std::string& _Path)
{
}

void GameEngineSound::SoundPlay(const std::string& _Name)
{
}

void GameEngineSound::PlayBgm(const std::string& _Name)
{
}

void GameEngineSound::StopBgm()
{
}
