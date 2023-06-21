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
	std::string State = "";
	bool Once = false;

	class Button* BtnOut = nullptr;
	class Curtain* CurtainPtr = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void StateUpdate(float _Delta);
	void StartUpdate(float _Delta);
	void InGameUpdate(float _Delta);
	void WinUpdate(float _Delta);
	void LoseUpdate(float _Delta);

	void CuratinUpdate(float _Delta);
	void PlayerCheck();
	void MonsterCheck();
	void OutButtonUpdate(float _Delta);
};
