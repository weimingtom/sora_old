// Ŭnicode please
#include "matsu/vector.h"

namespace matsu
{
template<typename T>
bool EqualAbsoluteError(T a, T b, T maxError)
{
	if(a == b)
	{
		return true;
	}
	if(abs(a - b) <= maxError)
	{
		return true;
	}
	//else..
	return false;
}
	
template<typename T>
bool EqualRelativeError(T a, T b, T maxError)
{
	if(fabs(a - b) < maxError)
	{
		return true;
	}
	T relativeError = 0;
	if(abs(b) > abs(a))
	{
		relativeError = abs((a-b) / b);
	}
	else
	{
		relativeError = abs((a-b) / a);
	}
	if(relativeError <= maxError)
	{
		return true;
	}
	//else..
	return false;
}
	
template<typename T>
bool EqualUlps(T a, T b, int maxUlps)
{
	//http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
	SR_ASSERT(sizeof(float) == sizeof(int));
	if (a == b)
	{
		return true;
	}
	int intDiff = abs(*(int*)&a - *(int*)&b);
	if (intDiff <= maxUlps)
	{
		return true;
	}
	return false;
}
	
template<typename T>
bool IsPower(T base, T target)
{
	if(target < 1)
	{
		//2*-1=0.5인데 이런 경우는 쓰지 않을듯해서 신경쓰지 않는다
		//어차피 위와같이 분수로 내려가는 경우, 정밀도 문제로
		//쓰지도 못할거같다
		return false;
	}
	T curr = base;
	while(curr <= target)
	{
		if(curr == target)
		{
			return true;
		}
		curr *= base;
	}
	return false;
}
	
template<typename T>
T CeilPower(T base, T target)
{
	if(target < 1)
	{
		//소수점이하는 계산무시
		return base;
	}
	T curr = base;
	while(curr < target)
	{
		curr *= base;
	}
	return curr;
}

template<typename T>
bool IsNaN(T num)
{
	return (num != num);
}

template<typename T>
bool IsINF(T num)
{
	if(std::numeric_limits<T>::has_infinity == false)
	{
		return false;
	}
	if(num == std::numeric_limits<T>::infinity())
	{
		return true;
	}
	//else..
	return false;
}

template<typename T>
bool IsNormalNumber(T num)
{
	if(IsNaN(num) || IsINF(num))
	{
		return false;
	}
	//else...
	return true;
}

template<typename T>
T StringToInt(const std::string &str)
{
	int result = atoi(str.c_str());
	return static_cast<T>(result);
}
	
template<typename T>
T StringToFloat(const std::string &str)
{
	//double이 큰 형태이고 원래 atof의 타입이 double더라
	double result = atof(str.c_str());
	return static_cast<T>(result);
}
	
template<typename T>
T CalculateIncludeAngleDegree(T src, T dst)
{
	T radResult = CalculateIncludeAngleRadian(DegreeToRadian(src), DegreeToRadian(dst));
	return rad2deg(radResult);
}
	
template<typename T>
T CalculateIncludeAngleRadian(T src, T dst)
{
	vec2 srcVec2(cos(src), sin(src));
	vec2 dstVec2(cos(dst), sin(dst));
	float vecDot = srcVec2.Dot(dstVec2);
	float srcSize = srcVec2.Size();
	float dstSize = dstVec2.Size();
	float value = vecDot / srcSize / dstSize;
	if(value >= 1.0f) {
		value = 1.0f;
	} else if(value <= -1.0f) {
		value = -1.0f;
	}
	float rawAbsRadian = acos(value);
	SR_ASSERT(IsNaN(rawAbsRadian) == false);
		
	//벡터의 외적을 이용해서 zero-curr이 양수방향인지 음수방향인지를 결정한다
	vec3 srcVec3(srcVec2);
	vec3 dstVec3(dstVec2);
	vec3 crossPan = srcVec3.Cross(dstVec3);
	if(crossPan.GetZ() > 0) {
		return rawAbsRadian;
	} else {
		return -rawAbsRadian;
	}
}
/*	
template<typename T>
T asinRad(T value, T maxError)
{
	T result = 0;
	if(value >= static_cast<T> (1.0) && value <= static_cast<T> (1.0 + maxError)) 
	{
		value = static_cast<T> (1.0);
	}
	else if(value <= static_cast<T> (-1.0) && value >= static_cast<T>(-1.0 + maxError))
	{
		value = static_cast<T> (-1.0);
	}
	else if(value >= static_cast<T> (-1.0) && value <= static_cast<T> (1))
	{
		; //정상 범위
	}
	else
	{
		SR_ASSERT(!"not valid value, check range -1~1");
	}
	return asin(value);

}
template<typename T>
T asinDeg(T value, T maxError)
{
	return asinRad(DegreeToRadian(value, maxError));
}
	
template<typename T>
T acosRad(T value, T maxError)
{
	T result = 0;
	if(value >= static_cast<T> (1.0) && value <= static_cast<T> (1.0 + maxError)) 
	{
		value = static_cast<T> (1.0);
	}
	else if(value <= static_cast<T> (-1.0) && value >= static_cast<T>(-1.0 + maxError))
	{
		value = static_cast<T> (-1.0);
	}
	else if(value >= static_cast<T> (-1.0) && value <= static_cast<T> (1))
	{
		; //정상 범위
	}
	else
	{
		SR_ASSERT(!"not valid value, check range -1~1");
	}
	return acos(value);
}
template<typename T>
T acosDeg(T value, T maxError)
{
	return acosDeg(DegreeToRadian(value, maxError));
}
	
template<typename T>
T atanRad(T value)
{
	return atan(value);
}
template<typename T>
T atanDeg(T value)
{
	return atanRad(DegreeToRadian(value));
}
*/
template<typename T>
T Lerp(T from, T to, float t)
{
	return from * (1-t) + to * t;
}
}