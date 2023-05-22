#include "Global.h"

int2 PosToIndex(const float4& _Pos)
{
	return ((_Pos - MapLeftTop) / TileSize).ToInt2();
}

float4 IndexToPos(const int2& _Index)
{
	return _Index.ToFloat4() * TileSize + MapLeftTop + TileSize.Half();
}