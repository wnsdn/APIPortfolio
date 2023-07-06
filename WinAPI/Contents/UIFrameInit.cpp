#include "UIFrame.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

void UIFrame::ItemSlotInit()
{
	CreateRenderer("ItemNeedle.bmp", RenderOrder::BackUI, { 1, 0 }, { 2, 1 });
	FindRenderer("ItemNeedle.bmp")->AddPos({ -146, 297 });
	FindRenderer("ItemNeedle.bmp")->AddScale({ -7, -7 });

	CreateRenderer("ItemShield.bmp", RenderOrder::BackUI, { 1, 0 }, { 2, 1 });
	FindRenderer("ItemShield.bmp")->AddPos({ -104, 297 });
	FindRenderer("ItemShield.bmp")->AddScale({ -7, -10 });

	CreateRenderer("ItemJump.bmp", RenderOrder::BackUI, { 1, 0 }, { 2, 1 });
	FindRenderer("ItemJump.bmp")->AddPos({ -62, 296 });
	FindRenderer("ItemJump.bmp")->AddScale({ -7, -10 });

	CreateRenderer("ItemSlot1.bmp", RenderOrder::BackUI, { 1, 0 }, { 2, 1 });
	FindRenderer("ItemSlot1.bmp")->AddPos({ -158, 287 });
	FindRenderer("ItemSlot1.bmp")->AddScale({ -11, -6 });

	CreateRenderer("ItemSlot2.bmp", RenderOrder::BackUI, { 1, 0 }, { 2, 1 });
	FindRenderer("ItemSlot2.bmp")->AddPos({ -116, 287 });
	FindRenderer("ItemSlot2.bmp")->AddScale({ -11, -6 });

	CreateRenderer("ItemSlot3.bmp", RenderOrder::BackUI, { 1, 0 }, { 2, 1 });
	FindRenderer("ItemSlot3.bmp")->AddPos({ -74, 287 });
	FindRenderer("ItemSlot3.bmp")->AddScale({ -11, -6 });
}

void UIFrame::CurItemInit()
{
	CreateRenderer("ItemNeedle.bmp", RenderOrder::BackUI, { 0, 0 }, { 2, 1 }, "CurItemNeedle");
	FindRenderer("CurItemNeedle")->AddPos({ 307, 220 });
	FindRenderer("CurItemNeedle")->Off();

	CreateRenderer("ItemShield.bmp", RenderOrder::BackUI, { 0, 0 }, { 2, 1 }, "CurItemShield");
	FindRenderer("CurItemShield")->AddPos({ 309, 220 });
	FindRenderer("CurItemShield")->Off();

	CreateRenderer("ItemJump.bmp", RenderOrder::BackUI, { 0, 0 }, { 2, 1 }, "CurItemJump");
	FindRenderer("CurItemJump")->AddPos({ 308, 220 });
	FindRenderer("CurItemJump")->Off();

	CreateRenderer("ItemX.bmp", RenderOrder::BackUI);
	FindRenderer("ItemX.bmp")->AddPos({ 351, 232 });
	FindRenderer("ItemX.bmp")->AddScale({ -6, -5 });
	FindRenderer("ItemX.bmp")->Off();

	CreateRenderer("Item0.bmp", RenderOrder::BackUI);
	FindRenderer("Item0.bmp")->AddPos({ 364, 231 });
	FindRenderer("Item0.bmp")->AddScale({ -9, -5 });
	FindRenderer("Item0.bmp")->Off();

	CreateRenderer("ItemNum.bmp", RenderOrder::BackUI, {0, 0}, { 1, 6 });
	FindRenderer("ItemNum.bmp")->AddPos({ 379, 231 });
	FindRenderer("ItemNum.bmp")->AddScale({ -10, -5 });
	FindRenderer("ItemNum.bmp")->Off();
}
