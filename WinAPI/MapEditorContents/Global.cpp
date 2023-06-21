#include "Global.h"

float4 PosToIndexPos(const float4& _Pos, const float4& _LeftTop, const float4& _Size)
{
	int2 Index = ((_Pos - _LeftTop) / _Size).ToInt2();
	float4 Pos = Index.ToFloat4() * _Size + _LeftTop + _Size.Half();

	return Pos;
}

int2 PosToIndex(const float4& _Pos, const float4& _LeftTop, const float4& _Size)
{
	int2 Index = ((_Pos - _LeftTop) / _Size).ToInt2();
	return Index;
}
