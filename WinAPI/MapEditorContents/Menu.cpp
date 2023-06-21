#include "Menu.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Button.h"

Menu* Menu::MainMenu;

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Start()
{
	CreateRenderer("Tile1x1.bmp", RenderOrder::UI);
	FindRenderer("Tile1x1.bmp")->SetPos({ 42 * 15 + 205, 200 });
	FindRenderer("Tile1x1.bmp")->Off();
	CreateRenderer("1x1_1.bmp", RenderOrder::UI);
	FindRenderer("1x1_1.bmp")->SetPos({ 42 * 15 + 205, 360 });
	FindRenderer("1x1_1.bmp")->Off();
	CreateRenderer("Object.bmp", RenderOrder::UI);
	FindRenderer("Object.bmp")->SetPos({ 42 * 15 + 235, 360 });
	FindRenderer("Object.bmp")->Off();
	CreateRenderer("Item.bmp", RenderOrder::UI);
	FindRenderer("Item.bmp")->SetPos({ 42 * 15 + 83, 57 + 2 });
	FindRenderer("Item.bmp")->Off();
	CreateRenderer("Position.bmp", RenderOrder::UI);
	FindRenderer("Position.bmp")->SetPos({ 42 * 15 + 65, 22 });
	FindRenderer("Position.bmp")->Off();

	CurRenderer = FindRenderer("Tile1x1.bmp");

	InsertRenderer();

	Prev = Level->CreateActor<Button>(UpdateOrder::UI);
	Prev->Init({ 470, 600 }, "Prev");
	Next = Level->CreateActor<Button>(UpdateOrder::UI);
	Next->Init({ 580, 600 }, "Next");

	BtnGrid = Level->CreateActor<Button>(UpdateOrder::UI);
	BtnGrid->Init({ 80, 600 }, "Grid", true);
	BtnGrid->IsClick = true;
	Paint = Level->CreateActor<Button>(UpdateOrder::UI);
	Paint->Init({ 190, 600 }, "Paint", true);
	Paint->AddTextPos({ -2,0 });

	EraseAll = Level->CreateActor<Button>(UpdateOrder::UI);
	EraseAll->Init({ 80, 650 }, "EraseAll");
	EraseAll->AddTextPos({ -15,0 });
	Erase = Level->CreateActor<Button>(UpdateOrder::UI);
	Erase->Init({ 190, 650 }, "Erase", true);
	Erase->AddTextPos({ -5,0 });

	Open = Level->CreateActor<Button>(UpdateOrder::UI);
	Open->Init({ 80, 700 }, "Open");
	Open->AddTextPos({ -5,0 });
	Save = Level->CreateActor<Button>(UpdateOrder::UI);
	Save->Init({ 190, 700 }, "Save");
}

void Menu::Update(float _Delta)
{
	MenuUpdate();
	GridUpdate();
	ButtonUpdate();
}

void Menu::Render(float _Delta)
{
	MenuRender();
	GridRender();
}

