#pragma once

struct Vec2
{
public:
	Vec2();
	Vec2(const Vec2& Vec);
	Vec2(float inX, float inY);

	float x;
	float y;
};