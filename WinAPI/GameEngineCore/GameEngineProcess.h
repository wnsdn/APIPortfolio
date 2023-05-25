#pragma once
#include <map>
#include <GameEngineBase/GameEngineString.h>
#include "GameEngineObject.h"

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

	template <typename LevelType>
	LevelType* CreateLevel(const std::string& _LevelName)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_LevelName);
		auto FindIter = AllLevel.find(Upper);
		
		if (FindIter != AllLevel.end())
		{
			return dynamic_cast<LevelType*>(FindIter->second);
		}

		class GameEngineLevel* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.emplace(std::make_pair(Upper, NewLevel));
		NextLevel = NewLevel;

		return dynamic_cast<LevelType*>(NewLevel);
	}
	class GameEngineLevel* FindLevel(const std::string& _LevelName);
protected:
	class GameEngineLevel* CurLevel = nullptr;
	class GameEngineLevel* NextLevel = nullptr;
	std::map<std::string, class GameEngineLevel*> AllLevel;
private:
	void LevelInit(class GameEngineLevel* _Level);
	void LevelUpdate(float _Delta);
	void LevelRender();
	void LevelRelease();
};