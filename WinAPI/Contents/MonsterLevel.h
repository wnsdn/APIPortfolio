#pragma once
#include <string>
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

	void Init(const std::string& _MapData);
private:
	bool Win = false;
	bool Lose = false;

	class Button* BtnOut = nullptr;
	class Curtain* CurtainPtr = nullptr;
	class GameResult* ResultPtr = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void OutButtonUpdate(float _Delta);
};
