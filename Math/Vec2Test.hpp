#include "TestSuite.hpp"
#include "Math.hpp"

using namespace Math;

TEST(Vec2, Bounce, "Bounce ray off normal")
{
	Vec2 dir;
	Vec2 norm;
	Vec2 bounce;

	dir = Vec2(2, 0);
	norm = Vec2(-1, 1);
	bounce = dir.bounce(norm);
	EXPECT(bounce, == , Vec2(0, 2));

	dir = Vec2(2, 0);
	norm = Vec2(0, 1);
	bounce = dir.bounce(norm);
	EXPECT(bounce, == , Vec2(2, 0));
}
TEST(Vec2, Rotate, "Rotate")
{
	Vec2 dir;
	Vec2 rot;

	dir = Vec2(3, 0);
	rot = dir.rotate(Math::Tau / 4.0f); // 90 degrees
	EXPECT(rot.x, < , 0.01);
	EXPECT(rot.y, == , 3);
}
TEST(Vec2, Angle, "Measure Angle")
{
	Vec2 dir(2, 2);
	int angle = static_cast<int>(Math::toDeg(dir.toAngle()));
	EXPECT(angle, == , 45);
}