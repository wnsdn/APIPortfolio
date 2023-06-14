#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineTexture.h>
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
}

void GameEngineRenderer::CreateTexture(const std::string& _Filename, const float4& _Size, unsigned int _Color)
{
	Texture = ResourceManager::GetInst().CreateTexture(_Filename, _Size);
	Texture->FillTexture(_Color);

	Pos = {};
	Scale = Texture->GetScale();
	CopyPos = {};
	CopyScale = Texture->GetScale();
}

void GameEngineRenderer::Render(float _Delta)
{
	if (Text != "")
	{
		TextRender(_Delta);
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
	float4 TextPos = Actor->GetPos() + Pos - Camera->GetPos();

	HDC Hdc = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();
	HFONT Hfont = nullptr, OldFont = nullptr;
	LOGFONTA Lf{};
	Lf.lfHeight = TextScale;
	Lf.lfCharSet = HANGEUL_CHARSET;
	Lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	lstrcpy(Lf.lfFaceName, Face.c_str());
	Hfont = CreateFontIndirectA(&Lf);
	OldFont = static_cast<HFONT>(SelectObject(Hdc, Hfont));

	SetTextColor(Hdc, RGB(255, 0, 0));
	SetBkMode(Hdc, TRANSPARENT);

	RECT Rect{};
	Rect.left = TextPos.iX();
	Rect.top = TextPos.iY();
	Rect.right = TextPos.iX() + TextScale * static_cast<int>(Text.size());
	Rect.bottom = TextPos.iY() + TextScale;

	DrawTextA(Hdc, Text.c_str(), static_cast<int>(Text.size()), &Rect,
		static_cast<UINT>(DT_BOTTOM));

	SelectObject(Hdc, OldFont);
	DeleteObject(Hfont);
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
