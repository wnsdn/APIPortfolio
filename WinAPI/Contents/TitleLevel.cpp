#include "TitleLevel.h"
#include "Global.h"
#include "BackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	BackGround* NewBackGround = CreateActor<BackGround>(UpdateOrder::None);
	NewBackGround->Init("BG\\Main");
}

void TitleLevel::Update(float _Delta)
{

}
