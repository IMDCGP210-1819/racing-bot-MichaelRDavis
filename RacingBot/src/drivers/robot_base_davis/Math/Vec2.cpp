#include "../Math/Vec2.h"
#include <cmath>

Vec2::Vec2()
{

}

Vec2::Vec2(const Vec2& Vec)
{

}

Vec2::Vec2(float inX, float inY)
{

}

Vec2 Vec2::operator+(const Vec2& Vec) const
{
	return Vec2(x + Vec.x, y + Vec.y);
}

Vec2 Vec2::operator*(const Vec2& Vec) const
{
	return Vec2(x * Vec.x, y * Vec.y);
}

Vec2 Vec2::operator*(float Scale) const
{
	return Vec2(x * Scale, y * Scale);
}

Vec2 Vec2::operator/(const Vec2& Vec) const
{
	return Vec2(x / Vec.x, y / Vec.y);
}

Vec2 Vec2::operator-(const Vec2& Vec) const
{
	return Vec2(x - Vec.x, y - Vec.y);
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

float Vec2::DotProduct(const Vec2& Vec)
{
	return x * Vec.x + y * Vec.y;
}

float Vec2::Length() const
{
	return sqrt(x * x + y * y);
}

void Vec2::Normalize()
{
	float a = this->Length();
	x /= a;
	y /= a;
}

float Vec2::Distance(const Vec2& Vec) const
{
	return sqrt(Vec.x - x) * (Vec.x - x) + (Vec.y - y) * (Vec.y - y);
}

float Vec2::Cosalpha(const Vec2& Vec, const Vec2& Center) const
{
	Vec2 VecA = *this - Center;
	Vec2 VecB = Vec - Center;
	return 0.0f; //(VecA * VecB) / (VecA.Length() * VecB.Length());
}

Vec2 Vec2::Rotate(const Vec2& Vec, float Arc) const
{
	Vec2 a = *this - Vec;
	float SinA = sin(Arc);
	float CosA = cos(Arc);
	return Vec + Vec2(a.x * CosA - a.y * SinA, a.x * SinA + a.y * CosA);
}

Vec2& Vec2::operator=(const Vec2& Vec)
{
	x = Vec.x;
	y = Vec.y;
	return *this;
}
