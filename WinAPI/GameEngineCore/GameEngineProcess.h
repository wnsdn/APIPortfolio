#pragma once
#include <map>
#include <GameEngineBase/GameEngineString.h>
#include "GameEngineObject.h"

class GameEngineLevel;
class GameEngineProcess : public GameEngineObject
{
	friend class GameEngineCore;
public:
	GameEngineProcess();
	virtual ~GameEngineProcess();
	GameEngineProcess(const GameEngineProcess& _Other) = delete;
	GameEngineProcess(GameEngineProcess&& _Other) noexcept = delete;
	GameEngineProcess& operator=(const GameEngineProcess& _Other) = delete;
	GameEngineProcess& operator=(GameEngineProcess&& _Other) noexcept = delete;

	template<typename LevelType>
	LevelType* CreateLevel(const std::string& _Level)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Level);
		auto FindIter = AllLevel.find(Upper);
		
		if (FindIter != AllLevel.end())
		{
			return dynamic_cast<LevelType*>(FindIter->second);
		}

		GameEngineLevel* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.emplace(Upper, NewLevel);
		NextLevel = NewLevel;

		return dynamic_cast<LevelType*>(NewLevel);
	}
	GameEngineLevel* FindLevel(const std::string& _Level);
protected:
	std::map<std::string, GameEngineLevel*> AllLevel;
	GameEngineLevel* NextLevel = nullptr;
	GameEngineLevel* CurLevel = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;

	void LevelInit(GameEngineLevel* _Level);
};