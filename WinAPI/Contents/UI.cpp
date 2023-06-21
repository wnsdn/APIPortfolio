#include "UI.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Init(const std::string& _Path, const float4& _Pos, int _RenderOrder)
{
	Main = _Path;
	Pos = _Pos;

	CreateRenderer(Main, _RenderOrder);

	InsertRenderer();
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
