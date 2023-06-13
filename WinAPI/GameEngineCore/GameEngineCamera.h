#pragma once
#include <map>
#include <list>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include "GameEngineSubObject.h"

class GameEngineRenderer;
class GameEngineCamera : public GameEngineObject, public GameEngineSubObject
{
public:
	GameEngineCamera();
	~GameEngineCamera();
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	template<typename EnumTypeBegin, typename EnumTypeEnd>
	void Init(EnumTypeBegin _ZOrderBegin, EnumTypeEnd _ZOrderEnd)
	{
		ZOrderBegin = static_cast<int>(_ZOrderBegin);
		ZOrderEnd = static_cast<int>(_ZOrderEnd);
	}
	void InsertRenderer(GameEngineRenderer* _Renderer);

	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release();
private:
	int ZOrderBegin = 0;
	int ZOrderEnd = 0;

	std::map<int, std::list<GameEngineRenderer*>> AllRenderer;
};