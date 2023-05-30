#pragma once
#include <map>
#include <list>
#include "GameEngineObject.h"

class GameEngineActor;
class GameEngineCamera;
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
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}
	template<typename ActorType>
	ActorType* CreateActor(int _Order)
	{
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename EnumType>
	std::list<GameEngineActor*> FindActor(EnumType _Order)
	{
		return AllActor[static_cast<int>(_Order)];
	}

	GameEngineCamera* GetMainCamera() const
	{
		return MainCamera;
	}
protected:
	std::map<int, std::list<GameEngineActor*>> AllActor;
	GameEngineCamera* MainCamera = nullptr;

	bool IsDebugRender = false;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;

	void ActorInit(GameEngineActor* _Actor);
};