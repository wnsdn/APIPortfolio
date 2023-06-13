#pragma once
#include <GameEngineCore/GameEngineProcess.h>

class CoreProcess : public GameEngineProcess
{
public:
	CoreProcess();
	~CoreProcess();
	CoreProcess(const CoreProcess& _Other) = delete;
	CoreProcess(CoreProcess&& _Other) noexcept = delete;
	CoreProcess& operator=(const CoreProcess& _Other) = delete;
	CoreProcess& operator=(CoreProcess&& _Other) noexcept = delete;
private:
	void Start() override;
};