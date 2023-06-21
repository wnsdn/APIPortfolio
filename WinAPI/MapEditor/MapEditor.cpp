#include <GameEngineCore/GameEngineCore.h>
#include <MapEditorContents/CoreProcess.h>

int WINAPI WinMain(_In_ HINSTANCE _Hinst, _In_opt_ HINSTANCE, _In_ char*, _In_ int)
{
	GameEngineCore::EngineStart<CoreProcess>(_Hinst, "MapEditor");
	return 0;
}