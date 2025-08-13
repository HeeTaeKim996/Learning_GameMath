
#include "Precompiled.h"
using namespace CK;

#if 0 // 원본
Box::Box(const std::vector<Vector3> InVertices)
{
	for (const auto& v : InVertices)
	{
		*this += v;
	}
}
#endif // 원본


















































































#if 1 // 공부
Box::Box(const std::vector<Vector3> InVertices)
{
	for (const Vector3& v : InVertices)
	{
		*this += v;
	}
}

/* 
	- Box.h 의 operator += 함수를 통해, 기존 Box 의 Min XYZ, Max XYZ 위 InVertices 들을 하나 하나 구분하여,
	  Min XYZ, Max XYZ 를 갱신
*/


#endif // 공부


