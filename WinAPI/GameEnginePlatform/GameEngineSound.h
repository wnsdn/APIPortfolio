#pragma once
#include <string>
#include <map>
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

class GameEngineSound
{
public:
	GameEngineSound();
	~GameEngineSound();
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

	static void Init();
	static void Release();
	static void Update();
	static void CreateSound(const std::string& _Filename, bool _Loop = false);
	static GameEngineSound* FindSound(const std::string& _Filename);

	void Play();
	void Stop();
	void SetVolume(float _Volume);
private:
	static FMOD::System* SoundSystem;
	static std::map<std::string, GameEngineSound*> AllSound;

	FMOD::Sound* SoundHandle = nullptr;
	FMOD::Channel* SoundControl = nullptr;

	void Load(const std::string& _Path, bool _Loop = false);
};

