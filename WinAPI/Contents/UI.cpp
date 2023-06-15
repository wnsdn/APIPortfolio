#include "UI.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Init(const std::string& _Filename, const float4& _Pos, int _ZOrder)
{
	Main = _Filename;
	Pos = _Pos;

	CreateRenderer(Main, _ZOrder, RenderOrder::None);
}

void UI::SetRendererScale(const float4& _Scale)
{
	FindRenderer(Main)->SetScale(_Scale);
}

void UI::AddRendererScale(const float4& _Scale)
{
	FindRenderer(Main)->AddScale(_Scale);
}

void UI::OnRenderer()
{
	FindRenderer(Main)->On();
}

void UI::OffRenderer()
{
	FindRenderer(Main)->Off();
}
