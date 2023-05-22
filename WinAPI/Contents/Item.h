#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Item : public GameEngineActor
{
public:
	Item();
	~Item();
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	void Init(const int2& _Index, const std::string& _Path);
private:
	void Update(float _Delta) override;
	void Render() override;
};