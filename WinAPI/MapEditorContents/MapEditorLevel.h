#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class MapEditorLevel : public GameEngineLevel
{
public:
	MapEditorLevel();
	~MapEditorLevel();
	MapEditorLevel(const MapEditorLevel& _Other) = delete;
	MapEditorLevel(MapEditorLevel&& _Other) noexcept = delete;
	MapEditorLevel& operator=(const MapEditorLevel& _Other) = delete;
	MapEditorLevel& operator=(MapEditorLevel&& _Other) noexcept = delete;
private:
	void Start() override;
};