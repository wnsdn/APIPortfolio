#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Block : public GameEngineActor
{
public:
	Block();
	~Block();
	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;

	void Init(const int2& _Index, const std::string& _BlockSize, const float4& _Type);
private:
	void Update(float _Delta) override;
	void Render() override;
};