#include "Global.h"

int2 PosToIndex(const float4& _Pos)
{
	return ((_Pos - float4(MapLeft, MapTop)) / TileSize).ToInt2();
}

float4 IndexToPos(const int2& _Index)
{
	return _Index.ToFloat4() * TileSize + float4(MapLeft, MapTop) + TileSize.Half();
}