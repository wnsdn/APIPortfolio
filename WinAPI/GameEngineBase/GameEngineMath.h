#pragma once
#include <cmath>

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	float X = 0.f;
	float Y = 0.f;

	int iX() const
	{
		return static_cast<int>(X);
	}
	int iY() const
	{
		return static_cast<int>(Y);
	}
	float hX() const
	{
		return X * 0.5f;
	}
	float hY() const
	{
		return Y * 0.5f;
	}
	int ihX() const
	{
		return static_cast<int>(X * 0.5f);
	}
	int ihY() const
	{
		return static_cast<int>(Y * 0.5f);
	}

	float Length()
	{
		return sqrtf(X * X + Y * Y);
	}
	float4 Normalize()
	{
		float Len = Length();

		if (Length() == 0.0f)
		{
			return {};
		}

		return *this /= Len;
	}

	float Max()
	{
		return X > Y ? X : Y;
	}

	float4 Half() const
	{
		return { hX(), hY() };
	}
	class int2 ToInt2() const;

	float4 operator+(const float4& _Other) const
	{
		return { X + _Other.X, Y + _Other.Y };
	}
	float4 operator+(const float _Value) const
	{
		return { X + _Value, Y + _Value };
	}
	float4 operator-(const float4& _Other) const
	{
		return { X - _Other.X, Y - _Other.Y };
	}
	float4 operator-(const float _Value) const
	{
		return { X - _Value, Y - _Value };
	}
	float4 operator/(const float4& _Other) const
	{
		return { X / _Other.X, Y / _Other.Y };
	}
	float4 operator/(const float _Value) const
	{
		return { X / _Value, Y / _Value };
	}
	float4 operator*(const float4& _Other) const
	{
		return { X * _Other.X, Y * _Other.Y };
	}
	float4 operator*(const float _Value) const
	{
		return { X * _Value, Y * _Value };
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;

		return *this;
	}
	float4& operator+=(const float _Value)
	{
		X += _Value;
		Y += _Value;

		return *this;
	}
	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;

		return *this;
	}
	float4& operator-=(const float _Value)
	{
		X -= _Value;
		Y -= _Value;

		return *this;
	}
	float4& operator/=(const float4& _Other)
	{
		X /= _Other.X;
		Y /= _Other.Y;

		return *this;
	}
	float4& operator/=(const float _Value)
	{
		X /= _Value;
		Y /= _Value;

		return *this;
	}
	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;

		return *this;
	}
	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;

		return *this;
	}

	bool operator!()
	{
		return !X && !Y;
	}
	bool operator<(const float4& _Other)
	{
		return X < _Other.X && Y < _Other.Y;
	}
	bool operator>(const float4& _Other)
	{
		return X > _Other.X && Y > _Other.Y;
	}

	float4()
		: X(0.f), Y(0.f)
	{
	}
	float4(const float _X, const float _Y)
		: X(_X), Y(_Y)
	{
	}
	float4(const float4& _Other)
		: X(_Other.X), Y(_Other.Y)
	{
	}
	~float4()
	{
	}
};

class int2
{
public:
	static const int2 Left;
	static const int2 Right;
	static const int2 Up;
	static const int2 Down;

	int X;
	int Y;

	float4 ToFloat4() const
	{
		return { static_cast<float>(X), static_cast<float>(Y) };
	}

	int2 operator+(const int2& _Other)
	{
		return { X + _Other.X, Y + _Other.Y };
	}
	int2 operator*(const int2& _Other)
	{
		return { X * _Other.X, Y * _Other.Y };
	}
	int2 operator*(const int _Value)
	{
		return { X * _Value, Y * _Value };
	}

	bool operator==(const int2& _Other)
	{
		return X == _Other.X && Y == _Other.Y;
	}
	bool operator<(const int2& _Other)
	{
		return X < _Other.X && Y < _Other.Y;
	}
	bool operator>=(const int2& _Other)
	{
		return X >= _Other.X && Y >= _Other.Y;
	}

	int2()
		: X(0), Y(0)
	{
	}
	int2(const int _X, const int _Y)
		: X(_X), Y(_Y)
	{
	}
	int2(const int2& _Other)
  		: X(_Other.X), Y(_Other.Y)
	{
	}
	~int2()
	{
	}
};