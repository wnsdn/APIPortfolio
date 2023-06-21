#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI : public GameEngineActor
{
public:
	UI();
	~UI();
	UI(const UI& _Other) = delete;
	UI(UI&& _Other) noexcept = delete;
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;

	template<typename EnumType>
	void Init(const std::string& _Path, const float4& _Pos, EnumType _RenderOrder)
	{
		Init(_Path, _Pos, static_cast<int>(_RenderOrder));
	}
	virtual void Init(const std::string& _Path, const float4& _Pos, int _RenderOrder);

	void SetRendererScale(const float4& _Scale);
	void AddRendererScale(const float4& _Scale);
	void OnRenderer();
	void OffRenderer();
protected:
	std::string Main = "";
};