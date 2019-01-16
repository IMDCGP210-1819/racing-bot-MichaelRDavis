#include "../Math/Vec2.h"
#include <cmath>

Vec2::Vec2()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(const Vec2& vec)
{
	x = vec.x;
	y = vec.y;
}

Vec2::Vec2(float inX, float inY)
{
	x = inX;
	y = inY;
}

Vec2 Vec2::operator+(const Vec2& vec) const
{
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

Vec2 Vec2::operator*(const float scale) const
{
	return Vec2(x * scale, y * scale);
}

float Vec2::operator*(const Vec2& vec) const
{
	return x * vec.x + y * vec.y;
}

float Vec2::Length() const
{
	return sqrt(x * x + y* y);
}

void Vec2::Normlaize()
{
	float length = this->Length();
	x /= length;
	y /= length;
}

float Vec2::Distance(const Vec2& vec) const
{
	return sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
}

float Vec2::Cosalpha(const Vec2& point, const Vec2& center) const
{
	Vec2 a = *this - center;
	Vec2 b = point - center;
	return (a * b) / (a.Length() * b.Length());
}

Vec2 Vec2::Rotate(const Vec2& center, float arc) const
{
	Vec2 a = *this - center;
	float sinA = sin(arc);
	float cosA = cos(arc);
	return center + Vec2(a.x * cosA - a.y * sinA, a.x * sinA + a.y * cosA);
}

Vec2& Vec2::operator=(const Vec2& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}
