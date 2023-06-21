#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button : public GameEngineActor
{
public:
	Button();
	~Button();
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

	void Init(const float4& _Pos, const std::string& _Name, bool _IsToggle = false);
	void AddTextPos(const float4& _Pos);

	bool IsClick = false;
	bool IsToggle = false;
private:
	std::string Name{};
	int R = 0, G = 0, B = 0;

	void Update(float _Delta);
	void Render(float _Delta);
};