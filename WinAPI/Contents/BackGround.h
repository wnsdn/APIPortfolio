#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BackGround : public GameEngineActor
{
public:
	BackGround();
	~BackGround();
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _Path);
};