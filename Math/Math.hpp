#pragma once

#include "Convert.hpp"
#include "Random.hpp"
#include "Constant.hpp"
#include "Vec2.hpp"
#include "OOCore.hpp"

#ifdef MATH_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

namespace Math
{
#ifdef min
#undef min
#endif
	template<typename T>
	T min(T a, T b)
	{
		if(a < b)
			return a;
		else
			return b;
	}
#ifdef max
#undef max
#endif
	template<typename T>
	inline T max(T a, T b)
	{
		if(a > b)
			return a;
		else
			return b;
	}
#ifdef abs
#undef abs
#endif
	template<typename T>
	T abs(T a)
	{
		if(a < 0)
			return -T;
		else
			return a;
	}

	MATH_API float sqrt(float a);

	MATH_API float sin(float a);
	MATH_API float cos(float a);
	MATH_API float tan(float a);

	MATH_API float asin(float a);
	MATH_API float acos(float a);
	MATH_API float atan2(float y, float x);
}


