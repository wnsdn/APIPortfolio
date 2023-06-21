#pragma once
#include <map>
#include <list>
#include "GameEngineObject.h"

class GameEngineActor;
class GameEngineCamera;
class GameEngineProcess;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineProcess;
public:
	GameEngineLevel();
	virtual ~GameEngineLevel();
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _UpdateOrder)
	{
		return CreateActor<ActorType>(static_cast<int>(_UpdateOrder));
	}
	template<typename ActorType>
	ActorType* CreateActor(int _UpdateOrder)
	{
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_UpdateOrder].push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename EnumType>
	std::list<GameEngineActor*> FindActor(EnumType _UpdateOrder)
	{
		return AllActor[static_cast<int>(_UpdateOrder)];
	}

	GameEngineCamera* GetCamera() const
	{
		return Camera;
	}
	template<typename EnumTypeBegin, typename EnumTypeEnd>
	void SetCameraZOrder(EnumTypeBegin _ZOrderBegin, EnumTypeEnd _ZOrderEnd)
	{
		SetCameraZOrder(static_cast<int>(_ZOrderBegin), static_cast<int>(_ZOrderEnd));
	}
	void SetCameraZOrder(int _ZOrderBegin, int _ZOrderEnd);

	GameEngineProcess* GetProcess() const
	{
		return Process;
	}
	void SetProcess(GameEngineProcess* const _Process)
	{
		Process = _Process;
	}
	
	void SetIsRender(bool _IsRender)
	{
		IsRender = _IsRender;
	}
protected:
	std::map<int, std::list<GameEngineActor*>> AllActor;
	GameEngineCamera* Camera = nullptr;
	GameEngineProcess* Process = nullptr;

	bool IsRender = false;

	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	void ActorInit(GameEngineActor* _Actor);
};