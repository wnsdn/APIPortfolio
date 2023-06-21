#pragma once
#include <string>
#include <vector>

class ReadMapData
{
public:
	ReadMapData(const std::string& _Filename);
	~ReadMapData();
	ReadMapData(const ReadMapData& _Other) = delete;
	ReadMapData(ReadMapData&& _Other) noexcept = delete;
	ReadMapData& operator=(const ReadMapData& _Other) = delete;
	ReadMapData& operator=(ReadMapData&& _Other) noexcept = delete;

private:
	void SplitMapData(const std::string& _MapData, std::vector<std::string>& _TileData);
	void SplitTileData(const std::vector<std::string>& _TileData, std::vector<std::string>& _AttrData);
	void SplitAttrData(const std::vector<std::string>& _AttrData);
};
