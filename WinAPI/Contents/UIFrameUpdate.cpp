#include "UIFrame.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Player.h"

void UIFrame::ItemSlotUpdate(float _Delta)
{
	if (!Player::MainPlayer)
	{
		return;
	}

	if (Player::MainPlayer->GetItemNeedle())
	{
		FindRenderer("ItemSlot1.bmp")->SetCopyPos({ 0,0 });
		FindRenderer("ItemNeedle.bmp")->SetCopyPos({ 0,0 });
	}
	else
	{
		FindRenderer("ItemSlot1.bmp")->SetCopyPos({ 1,0 });
		FindRenderer("ItemNeedle.bmp")->SetCopyPos({ 1,0 });
	}
	if (Player::MainPlayer->GetItemShield())
	{
		FindRenderer("ItemSlot2.bmp")->SetCopyPos({ 0,0 });
		FindRenderer("ItemShield.bmp")->SetCopyPos({ 0,0 });
	}
	else
	{
		FindRenderer("ItemSlot2.bmp")->SetCopyPos({ 1,0 });
		FindRenderer("ItemShield.bmp")->SetCopyPos({ 1,0 });
	}
	if (Player::MainPlayer->GetItemJump())
	{
		FindRenderer("ItemSlot3.bmp")->SetCopyPos({ 0,0 });
		FindRenderer("ItemJump.bmp")->SetCopyPos({ 0,0 });
	}
	else
	{
		FindRenderer("ItemSlot3.bmp")->SetCopyPos({ 1,0 });
		FindRenderer("ItemJump.bmp")->SetCopyPos({ 1,0 });
	}
}

void UIFrame::CurItemUpdate(float _Delta)
{
	if (!Player::MainPlayer)
	{
		return;
	}

	if (Player::MainPlayer->GetCurItem() != "")
	{
		FindRenderer("ItemX.bmp")->On();
		FindRenderer("Item0.bmp")->On();
	}
	else if (Player::MainPlayer->GetCurItem() == "")
	{
		FindRenderer("ItemX.bmp")->Off();
		FindRenderer("Item0.bmp")->Off();
		FindRenderer("ItemNum.bmp")->Off();
		FindRenderer("CurItemNeedle")->Off();
		FindRenderer("CurItemShield")->Off();
		FindRenderer("CurItemJump")->Off();
	}

	if (Player::MainPlayer->GetCurItem() == "Needle")
	{
		FindRenderer("CurItemNeedle")->On();
		FindRenderer("CurItemShield")->Off();
		FindRenderer("CurItemJump")->Off();
		FindRenderer("ItemNum.bmp")->On();
		int ItemNum = Player::MainPlayer->GetItemNeedle();
		FindRenderer("ItemNum.bmp")->SetCopyPos({ 0, static_cast<float>(ItemNum - 1) });
	}
	else if (Player::MainPlayer->GetCurItem() == "Shield")
	{
		FindRenderer("CurItemNeedle")->Off();
		FindRenderer("CurItemShield")->On();
		FindRenderer("CurItemJump")->Off();
		FindRenderer("ItemNum.bmp")->On();
		int ItemNum = Player::MainPlayer->GetItemShield();
		FindRenderer("ItemNum.bmp")->SetCopyPos({ 0, static_cast<float>(ItemNum - 1) });
	}
	else if (Player::MainPlayer->GetCurItem() == "Jump")
	{
		FindRenderer("CurItemNeedle")->Off();
		FindRenderer("CurItemShield")->Off();
		FindRenderer("CurItemJump")->On();
		FindRenderer("ItemNum.bmp")->On();
		int ItemNum = Player::MainPlayer->GetItemJump();
		FindRenderer("ItemNum.bmp")->SetCopyPos({ 0, static_cast<float>(ItemNum - 1) });
	}
}
