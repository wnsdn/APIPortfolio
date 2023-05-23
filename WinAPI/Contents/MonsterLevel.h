#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class MonsterLevel : public GameEngineLevel
{
public:
	MonsterLevel();
	~MonsterLevel();
	MonsterLevel(const MonsterLevel& _Other) = delete;
	MonsterLevel(MonsterLevel&& _Other) noexcept = delete;
	MonsterLevel& operator=(const MonsterLevel& _Other) = delete;
	MonsterLevel& operator=(MonsterLevel&& _Other) noexcept = delete;
private:
	void ReadMapData();

	void Start() override;
	void Update(float _Delta) override;
};
