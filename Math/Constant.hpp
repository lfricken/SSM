#pragma once

#ifdef MATH_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

namespace Math
{
	const float Degrees = 360.f;
	const float Pi = 3.14159f;
	const float Tau = Pi*2.f;
	const float E = 2.71828f;
}
