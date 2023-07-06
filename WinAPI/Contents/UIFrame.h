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

	bool TimeOver() const
	{
		return !Minute && !SecTen && !Sec;
	}
private:
	int CurTime = 0;
	int MaxTime = 180;

	int Minute = 0;
	int SecTen = 0;
	int Sec = 0;

	void ItemSlotInit();
	void CurItemInit();

	void ItemSlotUpdate(float _Delta);
	void CurItemUpdate(float _Delta);
};