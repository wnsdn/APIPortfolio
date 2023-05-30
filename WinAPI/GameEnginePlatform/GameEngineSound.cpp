#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

FMOD::System* GameEngineSound::SoundSystem = nullptr;
std::map<std::string, GameEngineSound*> GameEngineSound::AllSound;

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
	if (SoundHandle)
	{
		SoundHandle->release();
		SoundHandle = nullptr;
	}
}

void GameEngineSound::Init()
{
	if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
	{
		MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
		return;
	}

	if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_INIT_NORMAL, nullptr))
	{
		MsgBoxAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�.");
		return;
	}
}

void GameEngineSound::Update()
{
	if (!SoundSystem)
	{
		MsgBoxAssert("SoundSystem�� �������� �ʾƼ� ���� ������Ʈ�� �������� �����ϴ�.");
		return;
	}

	SoundSystem->update();
}

void GameEngineSound::Release()
{
	for (auto& Pair : GameEngineSound::AllSound)
	{
		GameEngineSound* Sound = Pair.second;

		if (Sound)
		{
			delete Sound;
			Sound = nullptr;
		}
	}

	if (SoundSystem)
	{
		SoundSystem->close();
		SoundSystem->release();
		SoundSystem = nullptr;
	}
}

void GameEngineSound::CreateSound(const std::string& _Filename, bool _Loop)
{
	std::string Path = GameEnginePath::GetPath("Sound", _Filename).string();
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	auto FindIter = AllSound.find(Upper);

	if (FindIter != AllSound.end())
	{
		return;
	}

	GameEngineSound* NewSound = new GameEngineSound();
	NewSound->Load(Path, _Loop);

	AllSound.insert(std::make_pair(Upper, NewSound));
}

GameEngineSound* GameEngineSound::FindSound(const std::string& _Filename)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	auto FindIter = AllSound.find(Upper);

	if (FindIter == AllSound.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSound::Load(const std::string& _Path, bool _Loop)
{
	std::string UTF8 = GameEngineString::AnsiToUTF8(_Path);
	if (_Loop)
	{
		SoundSystem->createSound(UTF8.c_str(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);
	}
	else
	{
		SoundSystem->createSound(UTF8.c_str(), FMOD_DEFAULT, nullptr, &SoundHandle);
	}

	if (nullptr == SoundHandle)
	{
		MsgBoxAssert(_Path + "���� �ε忡 �����߽��ϴ�.");
		return;
	}
}

void GameEngineSound::Play()
{
	SoundSystem->playSound(SoundHandle, nullptr, false, &SoundControl);
}

void GameEngineSound::Stop()
{
	SoundControl->stop();
}

void GameEngineSound::SetVolume(float _Volume)
{
	SoundControl->setVolume(_Volume);
}

