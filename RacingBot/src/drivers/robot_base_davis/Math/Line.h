#pragma once

#include "../Math/Vec2.h"

class Line
{
public:
	Line();
	Line(float x, float y, float dX, float dY);
	Line(const Vec2& point, const Vec2& direction);

	Vec2 Intersect(const Line& line) const;

	float Distance(const Vec2& vec) const;

	Vec2 m_Point;
	Vec2 m_Distance;
};