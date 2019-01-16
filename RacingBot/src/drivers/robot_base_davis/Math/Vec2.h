#pragma once

struct Vec2
{
public:
	Vec2();
	Vec2(const Vec2& vec);
	Vec2(float inX, float inY);

	Vec2& operator=(const Vec2& vec);

	Vec2 operator+(const Vec2& vec) const;
	Vec2 operator-(const Vec2& vec) const;

	Vec2 operator-() const;

	Vec2 operator*(const float scale) const;

	float operator*(const Vec2& vec) const;

	friend Vec2 operator*(const float scale, const Vec2& vec);

	float Length() const;

	void Normlaize();

	float Distance(const Vec2& vec) const;

	float Cosalpha(const Vec2& point, const Vec2& center) const;

	Vec2 Rotate(const Vec2& center, float arc) const;

	float x;
	float y;
};