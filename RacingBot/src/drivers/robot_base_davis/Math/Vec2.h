#pragma once

struct Vec2
{
public:
	Vec2();
	Vec2(const Vec2& Vec);
	Vec2(float inX, float inY);

	Vec2& operator=(const Vec2& Vec);

	Vec2 operator+(const Vec2& Vec) const;
	Vec2 operator-(const Vec2& Vec) const;
	Vec2 operator*(const Vec2& Vec) const;
	Vec2 operator/(const Vec2& Vec) const;

	float DotProduct(const Vec2& a, const Vec2 b);

	float x;
	float y;
};