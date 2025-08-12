
#include "Precompiled.h"
using namespace CK;

#if 0 // 원본
Sphere::Sphere(const std::vector<Vector3>& InVertices)
{
	size_t cnt = InVertices.size();
	if (cnt == 0)
	{
		return;
	}

	Vector3 sum;
	for (const auto& v : InVertices)
	{
		sum += v;
	}

	Center = sum / (float)cnt;
	Vector3 farthestPoint = (*std::max_element(InVertices.begin(), InVertices.end(),
		[&](Vector3 const& lhs, Vector3 const& rhs)
		{
			return (Center - lhs).SizeSquared() < (Center - rhs).SizeSquared();
		}));
	Radius = (farthestPoint - Center).Size();
}
#endif // 원본

















































































#if 1 // 공부
Sphere::Sphere(const std::vector<Vector3>& InVertices)
{
	size_t cnt = InVertices.size();
	if (cnt == 0)
	{
		return;
	}

	Vector3 sum;
	for (const Vector3& v : InVertices)
	{
		sum += v;
	}

	Center = sum / (float)cnt;
	Vector3 farthestPoint = (*std::max_element(InVertices.begin(), InVertices.end(),
		[&](Vector3 const& lhs, Vector3 const& rhs)
		{
			return (Center - lhs).SizeSquared() < (Center - rhs).SizeSquared();
		}));
	/*	■ std::max_element
		 - (1)주소를 시작, (2)주소를 end 로, (3) 의 람다식을 기준으로, 람다식 true 시 result 갱신. 모두 조회후, 마지막으로 갱신된
		   result 요소의 주소를 리턴
		 - 첫 result 는 (1) 시작 주소
	*/
	Radius = (farthestPoint - Center).Size();
}


#endif // 공부
