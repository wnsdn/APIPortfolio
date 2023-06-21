#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MenuState
{
	Tile,
	Block,
	Object,
	Item,
	Position,
};

class Menu : public GameEngineActor
{
public:
	static Menu* MainMenu;

	Menu();
	~Menu();
	Menu(const Menu& _Other) = delete;
	Menu(Menu&& _Other) noexcept = delete;
	Menu& operator=(const Menu& _Other) = delete;
	Menu& operator=(Menu&& _Other) noexcept = delete;

	class GameEngineRenderer* CurRenderer = nullptr;
	
	int State = static_cast<int>(MenuState::Tile);

	float4 SelectPos{};
	int2 SelectIndex{};
	bool MenuIsClick = false;

	float4 GridPos{};
	float4 GridIndex{};

	class Button* Prev = nullptr;
	class Button* Next = nullptr;
	class Button* BtnGrid = nullptr;
	class Button* EraseAll = nullptr;
	class Button* Erase = nullptr;
	class Button* Paint = nullptr;

	class Button* Open = nullptr;
	class Button* Save = nullptr;

private:
	bool IsGrid = true;
	int R = 0, G = 0, B = 0;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void MenuUpdate();
	void GridUpdate();
	void ButtonUpdate();

	void MenuRender();
	void GridRender();
};