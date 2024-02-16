#pragma once





template <typename TYPE>
inline TYPE Clamp(const TYPE value, const TYPE min, const TYPE max)
{
	return std::max(std::min(max, value), min);
}


template <typename TYPE>
inline TYPE Clamp01(const TYPE value)
{
	return Clamp<TYPE>(value, 0, 1);
}

inline int ClampLoop(const int value, int min, int max)
{
	if (min > max)
	{
		const int tempMax = max;
		max = min;
		min = tempMax;
	}

	int result{ value };


	int range{ max - min };

	while (result > max)
		result -= range + 1;

	while (result < min)
		result += range + 1;

	return result;
}

inline void OneMinus(float& value)
{
	value = 1.0f - value;
}


inline float MapWave(const float time, const float min, const float max, const float repeatTime, const float startTime)
{
	const float amplitude{ (max - min) / 2.0f };
	const float intercept{ min + amplitude };
	const float pulsation{ 2 * float(M_PI) / repeatTime };
	const float phase{ 2 * float(M_PI) * startTime };

	return amplitude * sinf(pulsation * time + phase) + intercept;
}

inline float Lerp(const float a, const float b, float t)
{
	t = Clamp01(t);
	return  a + (b - a) * t;
}

inline float SmoothLerp(const float a, const float b, float t)
{
	t = Clamp01(t);
	return Lerp(a,b, MapWave(t, 0, 1, 2, -0.25f));
}

inline float SmoothEndLerp(const float a, const float b, float t)
{
	t = Clamp01(t);
	return Lerp(a, b, MapWave(t, -1, 1, 4, 0));
}

inline float SmoothStartLerp(const float a, const float b, float t)
{
	t = Clamp01(t);
	return Lerp(a, b, MapWave(t, 0, 2, 4, -0.25f));
}



//double SineLerp(double value, const double from, const double to)
	//{
	//	value = Clamp01(value);
	//	return from + (to - from) * (0.5 * sin(M_PI * value + (-M_PI / 2.0)) + 0.5);
	//}



	//inline double RandomRange(double min, double max)
	//{
	//	// Inverse in case of the oppiside
	//	if (min > max)
	//	{
	//		const double tempMax = max;
	//		max = min;
	//		min = tempMax;
	//	}

	//	const double randomAlpha{ double(rand()) / RAND_MAX };
	//	const double range{ max - min };

	//	return randomAlpha * range + min;
	//}


	//template<typename TYPE>
	//float RadToDeg(float radians)
	//{
	//	return radians / TYPE(M_PI) * 180;
	//}

	//template<typename TYPE>
	//TYPE DegToRad(TYPE degrees)
	//{
	//	return degrees / 180 * TYPE(M_PI);
	//}

	//float RandomRange(float min, float max)
	//{
	//	return float(RandomRange(double(min),double(max)));
	//}

	//int RandomRange(int min, int max)
	//{
	//	// Inverse in case of the oppiside
	//	if (min > max)
	//	{
	//		const int tempMax = max;
	//		max = min;
	//		min = tempMax;
	//	}

	//	return rand() % (max - min + 1) + min;
	//}

	//float GetDistanceBetween(Point2f fromPoint, Point2f toPoint)
	//{
	//	return sqrtf(powf(toPoint.x - fromPoint.x, 2) + powf(toPoint.y - fromPoint.y, 2));
	//}

	//float GetAngleDifference(float fromAngle, float toAngle)
	//{
	//	return atan2f(sinf(toAngle - fromAngle), cosf(toAngle - fromAngle));
	//}

	//float GetAngleToPoint(Point2f fromPoint, Point2f toPoint)
	//{
	//	return atan2(toPoint.y - fromPoint.y, toPoint.x - fromPoint.x);
	//}


