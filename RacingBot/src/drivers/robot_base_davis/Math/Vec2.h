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

	Vec2 operator*(float Scale) const;

	Vec2 operator-() const;

	float DotProduct(const Vec2& a);

	float Length() const;

	void Normalize();

	float Distance(const Vec2& Vec) const;

	float Cosalpha(const Vec2& Vec, const Vec2& Center) const;

	Vec2 Rotate(const Vec2& Vec, float Arc) const;

	float x;
	float y;
};