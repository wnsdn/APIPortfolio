#pragma once
#include <map>
#include <list>
#include "GameEngineObject.h"

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

	template <typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}
	template <typename ActorType>
	ActorType* CreateActor(int _Order)
	{
		class GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	class GameEngineCamera* GetBackUICamera() const
	{
		return BackUICamera;
	}
	class GameEngineCamera* GetMainCamera() const
	{
		return MainCamera;
	}
	class GameEngineCamera* GetFrontUICamera() const
	{
		return FrontUICamera;
	}

	template <typename EnumType>
	std::list<class GameEngineActor*> GetActorGroup(EnumType _Order)
	{
		return AllActor[static_cast<int>(_Order)];
	}

	bool IsActorRender = true;
protected:
	class GameEngineCamera* BackUICamera = nullptr;
	class GameEngineCamera* MainCamera = nullptr;
	class GameEngineCamera* FrontUICamera = nullptr;
	std::map<int, std::list<class GameEngineActor*>> AllActor;
private:
	void ActorInit(class GameEngineActor* _Actor);
	void ActorUpdate(float _Delta);
	void ActorRender();
	void ActorRelease();
};