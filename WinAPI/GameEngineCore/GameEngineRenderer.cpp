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

void GameEngineRenderer::Init(const std::string& _Path, const float4& _Pos, const float4& _Size)
{
	Texture = ResourceManager::GetInst().LoadTexture(_Path);

	RenderScale = Texture->GetScale() / _Size;
	CopyScale = Texture->GetScale() / _Size;
	CopyPos = _Pos;
}

void GameEngineRenderer::Render(float _Delta)
{
	if (CurAnimation)
	{
		CurAnimation->CurInter += _Delta;
		if (CurAnimation->CurInter >= CurAnimation->Inter)
		{
			CopyPos.X = static_cast<float>(CurAnimation->CurFrame);
			CopyPos.Y = static_cast<float>(CurAnimation->YFrame);

			if (CurAnimation->Inter)
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

				CurAnimation->CurInter -= CurAnimation->Inter;
			}
		}
	}

	GameEngineWindow::GetInst().GetBackBuffer()->TransCopy(Texture,
		Master->GetPos() + RenderPos - Camera->GetPos(),
		RenderScale,
		CopyPos * CopyScale,
		CopyScale);
}

void GameEngineRenderer::CreateAnimation(const std::string& _AnimationName,
	int _XFrame, int _YFrame, int _Count, float _Inter, bool _Loop)
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
	NewAnimation.EndFrame = _XFrame + (_Count - 1);
	NewAnimation.Inter = _Inter;
	NewAnimation.Loop = _Loop;

	AllAnimation.emplace(std::make_pair(Upper, NewAnimation));
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

	if(CurAnimation != &FindIter->second)
	{
		CurAnimation = &FindIter->second;
		CurAnimation->CurFrame = CurAnimation->StartFrame;
		CurAnimation->CurInter = CurAnimation->Inter;
	}
}
