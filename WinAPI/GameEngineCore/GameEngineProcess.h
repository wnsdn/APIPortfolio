#pragma once
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
	LevelType* CreateLevel()
	{
		GameEngineLevel* NewLevel = new LevelType();
		LevelInit(NewLevel);

		if (CurLevel)
		{
			PrevLevel = CurLevel;
		}

		NextLevel = NewLevel;

		return dynamic_cast<LevelType*>(NewLevel);
	}
protected:
	GameEngineLevel* PrevLevel = nullptr;
	GameEngineLevel* NextLevel = nullptr;
	GameEngineLevel* CurLevel = nullptr;

	void LevelInit(GameEngineLevel* _Level);

	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;
};