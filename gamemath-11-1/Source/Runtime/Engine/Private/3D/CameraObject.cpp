
#include "Precompiled.h"
using namespace CK::DDD;


#if 0 // 외적을 사용하여, 3개의 축 설정 원본

void CameraObject::SetLookAtRotation(const Vector3& InTargetPosition, const Vector3& InUp)
{
	Vector3 localX, localY, localZ;

	// 단위 Z축 생성
	localZ = (InTargetPosition - _Transform.GetPosition()).GetNormalize();
	// 시선 방향과 월드 Y축이 평행한 경우
	if (Math::Abs(localZ.Y) >= (1.f - SMALL_NUMBER))
	{
		// 특이 상황에서 로컬 X 좌표 값을 임의로 지정.
		localX = Vector3::UnitX;
	}
	else
	{
		localX = InUp.Cross(localZ).GetNormalize();
	}

	// 두 벡터가 직교하고 크기가 1이면 결과는 1을 보장
	localY = localZ.Cross(localX);

	_Transform.SetLocalAxes(localX, localY, localZ);
}
#endif

























































#if 1 // 외적을 사용하여, 3개의 축 설정 원본

void CameraObject::SetLookAtRotation(const Vector3& InTargetPosition, const Vector3& InUp)
{
	Vector3 localX, localY, localZ;

	localZ = (InTargetPosition - _Transform.GetPosition()).GetNormalize();

	if (Math::Abs(localZ.Y) >= (1.f - SMALL_NUMBER))
	{
		localX = Vector3::UnitX;
	}
	else
	{
		localX = InUp.Cross(localZ).GetNormalize();
		/*	※ InUp 을 u = (0, 1, 0) 으로 고정값으로 사용하지 않고, InUp 으로 변수로 받는 이유는,
			  u = (0, 1, ) 을 웬만하면 사용하긴 하지만, u = (0, -1, 0) 으로 하여, 
			  카메라가 의 정수리가 바닥을 향하는 (거꾸로) 상태의 렌더링이 필요할 때도 있어서라 함
		*/
	}

	localY = localZ.Cross(localX);

	_Transform.SetLocalAxes(localX, localY, localZ);
}
#endif
