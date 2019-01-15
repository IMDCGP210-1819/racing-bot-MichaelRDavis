#include "../Math/Vec2.h"
#include <cmath>

Vec2::Vec2()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(const Vec2& vec)
{
	Vec2(vec);
}

Vec2::Vec2(float inX, float inY)
{
	x = inX;
	y = inY;
}

Vec2 Vec2::operator+(const Vec2& vec) const
{

}

Vec2 Vec2::operator-(const Vec2& vec) const
{

}

Vec2 Vec2::operator-() const
{

}

Vec2 Vec2::operator*(const float scale) const
{

}

float Vec2::operator*(const Vec2& vec) const
{

}

float Vec2::Length() const
{

}

void Vec2::Normlaize()
{

}

float Vec2::Distnace(const Vec2& vec) const
{

}

float Vec2::Cosalpha(const Vec2& point, const Vec2& center) const
{

}

Vec2 Vec2::Rotate(const Vec2& center, float arc) const
{

}

Vec2& Vec2::operator=(const Vec2& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}
