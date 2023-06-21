#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineGraphics.h>
#include "ResourceManager.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::LoadTexture(const std::string& _Filename, const float4& _Pos, const float4& _Size)
{
	Texture = ResourceManager::GetInst().LoadTexture(_Filename);

	Pos = {};
	Scale = Texture->GetScale() / _Size;
	CopyPos = _Pos;
	CopyScale = Texture->GetScale() / _Size;
	AdjScale = CopyScale;
}

void GameEngineRenderer::CreateTexture(const std::string& _Filename, const float4& _Size, unsigned int _Color)
{
	Texture = ResourceManager::GetInst().CreateTexture(_Filename, _Size);
	Texture->FillTexture(_Color);

	Pos = {};
	Scale = Texture->GetScale();
	CopyPos = {};
	CopyScale = Texture->GetScale();
	AdjScale = CopyScale;
}

void GameEngineRenderer::Render(float _Delta)
{
	if (Text.Str != "")
	{
		TextRender(_Delta);
		return;
	}

	if (IsGauge)
	{
		GaugeRender(_Delta);
		return;
	}

	if (CurAnimation)
	{
		CurAnimation->CurInter += _Delta;
		if (CurAnimation->CurInter >= CurAnimation->Inter)
		{
			CopyPos.X = static_cast<float>(CurAnimation->CurFrame);
			CopyPos.Y = static_cast<float>(CurAnimation->YFrame);

			if (CurAnimation->Inter)
			{
				if (CurAnimation->Reverse)
				{
					--CurAnimation->CurFrame;
					if (CurAnimation->CurFrame < CurAnimation->EndFrame)
					{
						if (CurAnimation->Loop)
						{
							CurAnimation->CurFrame = CurAnimation->StartFrame;
						}
						else
						{
							++CurAnimation->CurFrame;
						}
					}
				}
				else
				{
					++CurAnimation->CurFrame;
					if (CurAnimation->CurFrame > CurAnimation->EndFrame)
					{
						if (CurAnimation->Loop)
						{
							CurAnimation->CurFrame = CurAnimation->StartFrame;
						}
						else
						{
							--CurAnimation->CurFrame;
						}
					}
				}

				CurAnimation->CurInter -= CurAnimation->Inter;
			}
		}
	}

	if (AlphaRender)
	{
		GameEngineWindow::GetInst().GetBackBuffer()->AlphaCopy(Texture,
			Actor->GetPos() + Pos - Camera->GetPos(),
			Scale,
			CopyPos * CopyScale,
			CopyScale,
			AlphaValue);
	}
	else
	{
		GameEngineWindow::GetInst().GetBackBuffer()->TransCopy(Texture,
			Actor->GetPos() + Pos - Camera->GetPos(),
			Scale,
			CopyPos * CopyScale,
			CopyScale);
	}
}

void GameEngineRenderer::TextRender(float _Delta)
{
	int2 TextPos = Actor->GetPos().ToInt2() + Pos.ToInt2() - Camera->GetPos().ToInt2();
	HDC BackDC = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();

	GameEngineGraphics::DrawGPText(BackDC, Text.Str, Text.Face, Text.Size, TextPos, Text.Outline, Text.Color);
}

void GameEngineRenderer::GaugeRender(float _Delta)
{
	GameEngineWindow::GetInst().GetBackBuffer()->TransCopy2(Texture,
		Actor->GetPos() + Pos - Camera->GetPos(),
		Scale - AdjPos,
		AdjPos,
		Scale - AdjPos);
}

void GameEngineRenderer::CreateAnimation(const std::string& _AnimationName,
	int _XFrame, int _YFrame, int _Count, float _Inter, bool _Loop, bool _Reverse)
{
	std::string Upper = GameEngineString::ToUpperReturn(_AnimationName);
	auto FindIter = AllAnimation.find(Upper);

	if (FindIter != AllAnimation.end())
	{
		return;
	}

	Animation NewAnimation = {};
	NewAnimation.StartFrame = _XFrame;
	NewAnimation.CurFrame = _XFrame;
	NewAnimation.YFrame = _YFrame;
	if (_Reverse)
	{
		NewAnimation.EndFrame = _XFrame - _Count + 1;
	}
	else
	{
		NewAnimation.EndFrame = _XFrame + (_Count - 1);
	}
	NewAnimation.Inter = _Inter;
	NewAnimation.Loop = _Loop;
	NewAnimation.Reverse = _Reverse;

	AllAnimation.emplace(Upper, NewAnimation);
}

void GameEngineRenderer::ChangeAnimation(const std::string& _AnimationName)
{
	std::string Upper = GameEngineString::ToUpperReturn(_AnimationName);
	auto FindIter = AllAnimation.find(Upper);

	if (FindIter == AllAnimation.end())
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다." + _AnimationName);
		return;
	}

	if (CurAnimation != &FindIter->second)
	{
		CurAnimation = &FindIter->second;
		CurAnimation->CurFrame = CurAnimation->StartFrame;
		CurAnimation->CurInter = CurAnimation->Inter;
		LiveTime = 0.0f;
	}
}

bool GameEngineRenderer::IsAnimationEnd(const std::string& _AnimationName)
{
	std::string Upper = GameEngineString::ToUpperReturn(_AnimationName);
	auto FindIter = AllAnimation.find(Upper);

	if (FindIter == AllAnimation.end())
	{
		MsgBoxAssert("존재하지 않는 애니메이션 IsAnimationEnd(). " + _AnimationName);
		return false;
	}

	if (&FindIter->second != CurAnimation)
	{
		return false;
	}

	int Count = 0;
	if (CurAnimation->Reverse)
	{
		Count = CurAnimation->StartFrame - CurAnimation->EndFrame + 1;
	}
	else
	{
		Count = CurAnimation->EndFrame - CurAnimation->StartFrame + 1;
	}
	if (!CurAnimation->AnimationEnd && LiveTime >= static_cast<float>(Count) * CurAnimation->Inter)
	{
		CurAnimation->AnimationEnd = true;
		LiveTime = 0.0f;
	}

	return CurAnimation->AnimationEnd;
}

void GameEngineRenderer::ResetAnimation(const std::string& _AnimationName)
{
	std::string Upper = GameEngineString::ToUpperReturn(_AnimationName);
	auto FindIter = AllAnimation.find(Upper);

	if (FindIter == AllAnimation.end())
	{
		MsgBoxAssert("존재하지 않는 애니메이션 ResetAnimation(). " + _AnimationName);
		return;
	}

	if (&FindIter->second != CurAnimation || CurAnimation->Loop)
	{
		return;
	}

	CurAnimation->CurFrame = CurAnimation->StartFrame;
	CurAnimation->AnimationEnd = false;
}