#pragma once
#include "UI.h"

class UIFrame : public UI
{
public:
	UIFrame();
	~UIFrame();
	UIFrame(const UIFrame& _Other) = delete;
	UIFrame(UIFrame&& _Other) noexcept = delete;
	UIFrame& operator=(const UIFrame& _Other) = delete;
	UIFrame& operator=(UIFrame&& _Other) noexcept = delete;

	void Init(const std::string& _Path);
	void Update(float _Delta) override;
private:
	int CurTime = 0;
	int MaxTime = 180;
};