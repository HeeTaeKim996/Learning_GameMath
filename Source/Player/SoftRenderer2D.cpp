
#include "Precompiled.h"
#include "SoftRenderer.h"
#include <random>

#include "defines.h"

using namespace CK::DD;
/*-----------------------------------------
				  PART 1
-----------------------------------------*/
#if 0 // EX_3_1__EX5_2

// 격자를 그리는 함수
void SoftRenderer::DrawGizmo2D()
{
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	// 그리드 색상
	LinearColor gridColor(LinearColor(0.8f, 0.8f, 0.8f, 0.3f));

	// 뷰의 영역 계산
	Vector2 viewPos = g.GetMainCamera().GetTransform().GetPosition();
	Vector2 extent = Vector2(_ScreenSize.X * 0.5f, _ScreenSize.Y * 0.5f);

	// 좌측 하단에서부터 격자 그리기
	int xGridCount = _ScreenSize.X / _Grid2DUnit;
	int yGridCount = _ScreenSize.Y / _Grid2DUnit;

	// 그리드가 시작되는 좌하단 좌표 값 계산
	Vector2 minPos = viewPos - extent;
	Vector2 minGridPos = Vector2(ceilf(minPos.X / (float)_Grid2DUnit), ceilf(minPos.Y / (float)_Grid2DUnit)) * (float)_Grid2DUnit;
	ScreenPoint gridBottomLeft = ScreenPoint::ToScreenCoordinate(_ScreenSize, minGridPos - viewPos);

	for (int ix = 0; ix < xGridCount; ++ix)
	{
		r.DrawFullVerticalLine(gridBottomLeft.X + ix * _Grid2DUnit, gridColor);
	}

	for (int iy = 0; iy < yGridCount; ++iy)
	{
		r.DrawFullHorizontalLine(gridBottomLeft.Y - iy * _Grid2DUnit, gridColor);
	}

	ScreenPoint worldOrigin = ScreenPoint::ToScreenCoordinate(_ScreenSize, -viewPos);
	r.DrawFullHorizontalLine(worldOrigin.Y, LinearColor::Red);
	r.DrawFullVerticalLine(worldOrigin.X, LinearColor::Green);
}

// 게임 오브젝트 목록


// 최초 씬 로딩을 담당하는 함수
void SoftRenderer::LoadScene2D()
{
	// 최초 씬 로딩에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();

}

// 게임 로직과 렌더링 로직이 공유하는 변수
#ifdef EX_3_1
Vector2 currentPosition(100.f, 100.f);
#endif
#ifdef EX_3_2
Vector2 CurrentPosition(100.f, 100.f);

#endif
#ifdef EX_4_1
Vector2 currentPosition;
float currentScale = 10.f;
#endif
#ifdef EX_4_4
Vector2 currentPosition;
float currentScale = 10.f;
float currentDegree = 0.f;
#endif
#ifdef EX_4_5
float currentDegree = 0.f;
#endif
#ifdef EX_5_1
Vector2 currentPosition;
float currentScale = 10.f;
float currentDegree = 0.f;

float rad2;
float cos2 = cosf(0);
float sin2 = sinf(0);
#endif
#ifdef EX_5_2
float currentShear = 0.f;
float currentScale = 10.f;
float currentDegree = 0.f;
#endif

// 게임 로직을 담당하는 함수
void SoftRenderer::Update2D(float InDeltaSeconds)
{
	// 게임 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();
	const InputManager& input = g.GetInputManager();

	// 게임 로직의 로컬 변수
#ifdef EX_3_1
	static float moveSpeed = 100.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis));
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;

	currentPosition += deltaPosition;

#endif // __EX_3_1
#ifdef EX_3_2
	static float moveSpeed = 100.f;
	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	CurrentPosition += deltaPosition;

#endif
#ifdef EX_4_1
	static float moveSpeed = 100.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;

	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
#endif
#ifdef EX_4_4
	static float moveSpeed = 100.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 180.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;

	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	currentDegree += deltaDegree;
#endif
#ifdef EX_4_5
	static float rotateSpeed = 180.f;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;

	currentDegree += deltaDegree;
#endif
#ifdef EX_5_1
	static float moveSpeed = 100.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 180.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds * 0.08;

	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	rad2 += deltaDegree;
	cos2 = cosf(rad2);
	sin2 = sinf(rad2);
#endif
#ifdef EX_5_2
	static float shearSpeed = 2.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 180.f;

	float deltaShear = input.GetAxis(InputAxis::XAxis) * shearSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;

	currentShear += deltaShear;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	currentDegree += deltaDegree;
#endif
}

// 렌더링 로직을 담당하는 함수
void SoftRenderer::Render2D()
{
	// 렌더링 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();


	// 배경에 격자 그리기
	DrawGizmo2D();

	// 렌더링 로직의 로컬 변수
#ifdef EX_3_1
	// 밝은 회색의 선을 사용해 평행한 벡터를 표현
	static float lineLength = 500.f;
	Vector2 lineStart = currentPosition * lineLength;
	Vector2 lineEnd = currentPosition * -lineLength;
	r.DrawLine(lineStart, lineEnd, LinearColor::LightGray);


	// 벡터를 파란색 픽셀로 표현
	r.DrawPoint(currentPosition, LinearColor::Blue);
	r.DrawPoint(currentPosition + Vector2::UnitX, LinearColor::Blue);
	r.DrawPoint(currentPosition - Vector2::UnitX, LinearColor::Blue);
	r.DrawPoint(currentPosition + Vector2::UnitY, LinearColor::Blue);
	r.DrawPoint(currentPosition - Vector2::UnitY, LinearColor::Blue);
	r.DrawPoint(currentPosition + Vector2::One, LinearColor::Blue);
	r.DrawPoint(currentPosition - Vector2::UnitX, LinearColor::Blue);
	r.DrawPoint(currentPosition + Vector2(1.f, -1.f), LinearColor::Blue);
	r.DrawPoint(currentPosition - Vector2(1.f, -1.f), LinearColor::Blue);

	// 벡터의 현재 좌표를 우상단에 출력
	r.PushStatisticText("Coordinate : " + currentPosition.ToString());


#endif
#ifdef EX_3_2
	static float radius = 50.f;
	static std::vector<Vector2> circles;

	if (circles.empty())
	{
		for (float x = -radius; x <= radius; ++x)
		{
			for (float y = -radius; y <= radius; ++y)
			{
				Vector2 pointToTest = Vector2(x, y);
				float squaredLength = pointToTest.SizeSquared();

				if (squaredLength <= radius * radius)
				{
					circles.push_back(Vector2(x, y));
				}
			}
		}
	}

	for (Vector2 const& v : circles)
	{
		r.DrawPoint(v + CurrentPosition, LinearColor::Red);
	}

	r.PushStatisticText("Coordinate : " + CurrentPosition.ToString());


#endif
#ifdef EX_4_1
	float rad = 0.f;
	static float increment = 0.001f;
	static std::vector<Vector2> hearts;


	if (hearts.empty())
	{
		for (rad = 0.f; rad < Math::TwoPI; rad += increment) // 신기하네.. 이해는 안했는데, 하트방정식이라고 다양하게 있다함
		{
			float sin = sinf(rad);
			float cos = cosf(rad);
			float cos2 = cosf(2 * rad);
			float cos3 = cosf(3 * rad);
			float cos4 = cosf(4 * rad);

			float x = 16.f * sin * sin * sin;
			float y = 13 * cos - 5 * cos2 - 2 * cos3 - cos4;
			hearts.push_back(Vector2(x, y));
		}
	}

	for (Vector2 const& v : hearts)
	{
		r.DrawPoint(v * currentScale + currentPosition, LinearColor::Blue);
	}




#endif 
#ifdef EX_4_4
	float rad = 0.f;
	static float increment = 0.001f;
	static std::vector<Vector2>hearts;
	HSVColor hsv(0.f, 1.f, 0.85f);

	if (hearts.empty())
	{
		for (rad = 0.f; rad < Math::TwoPI; rad += increment)
		{
			float sin = sinf(rad);
			float cos = cosf(rad);
			float cos2 = cosf(2 * rad);
			float cos3 = cosf(3 * rad);
			float cos4 = cosf(4 * rad);

			float x = 16.f * sin * sin * sin;
			float y = 13 * cos - 5 * cos2 - 2 * cos3 - cos4;

			hearts.push_back(Vector2(x, y));
		}
	}

	float sin = 0.f, cos = 0.f;
	Math::GetSinCos(sin, cos, currentDegree);

	rad = 0.f;
	for (Vector2 const& v : hearts)
	{
		Vector2 scaledV = v * currentScale;

		Vector2 rotatedV = Vector2(cos * scaledV.X - sin * scaledV.Y, sin * scaledV.X + cos * scaledV.Y); // 회전 적용

		Vector2 translatedV = rotatedV + currentPosition;

		// ※ SRT 적용 순서랑 같구나

		hsv.H = rad / Math::TwoPI;
		r.DrawPoint(translatedV, hsv.ToLinearColor());
		rad += increment;
	}
#endif
#ifdef EX_4_5
	static float halfSize = 100.f;
	static std::vector<Vector2> squares;

	if (squares.empty())
	{
		for (float x = -halfSize; x <= halfSize; x += 0.25f)
		{
			for (float y = -halfSize; y <= halfSize; y += 0.25f)
			{
				squares.push_back(Vector2(x, y));
			}
		}
	}

	float sin = 0.f, cos = 0.f;
	Math::GetSinCos(sin, cos, currentDegree);

	static float maxLength = Vector2(_ScreenSize.X, _ScreenSize.Y).Size() * 0.5f;

	HSVColor hsv(0.f, 1.f, 0.85f);
	for (Vector2 const& v : squares)
	{
		Vector2 polarV = v.ToPolarCoordinate();

		if (polarV.Y < 0.f)
		{
			polarV.Y += Math::TwoPI;
		}
		hsv.H = polarV.Y / Math::TwoPI;


		float ratio = polarV.X / maxLength; // 크기 에 비례하여, 회전량을 결정하기 위한 변수
		float weight = Math::Lerp(1.f, 5.f, ratio);

		polarV.Y += Math::Deg2Rad(currentDegree) * weight;

		Vector2 cartesianV = polarV.ToCartesianCoordinate();
		r.DrawPoint(cartesianV, hsv.ToLinearColor());
	}



#endif
#ifdef EX_5_1

	float rad = 0.f;
	static float increment = 0.001f;
	static std::vector<Vector2>hearts;
	HSVColor hsv(0.f, 1.f, 0.85f);

	if (hearts.empty())
	{
		for (rad = 0.f; rad < Math::TwoPI; rad += increment)
		{
			float sin = sinf(rad);
			float cos = cosf(rad);
			float cos2 = cosf(2 * rad);
			float cos3 = cosf(3 * rad);
			float cos4 = cosf(4 * rad);

			float x = 16.f * sin * sin * sin;
			float y = 13 * cos - 5 * cos2 - 2 * cos3 - cos4;

			hearts.push_back(Vector2(x, y));
		}
	}


	Vector2 rBsis1(cos2, sin2);
	Vector2 rBsis2(-sin2, cos2);
	Matrix2x2 rMatrix(rBsis1, rBsis2);

	Vector2 sBasis1 = Vector2::UnitX * currentScale;
	Vector2 sBasis2 = Vector2::UnitY * currentScale;
	Matrix2x2 sMatrix(sBasis1, sBasis2);

	Matrix2x2 finalMatrix = rMatrix * sMatrix;
	rad = 0.f;
	for (Vector2 const& v : hearts)
	{
		Vector2 transformedV = finalMatrix * v;
		Vector2 translatedV = transformedV + currentPosition;

		hsv.H = rad / Math::TwoPI;
		r.DrawPoint(translatedV, hsv.ToLinearColor());
		rad += increment;
	}


#endif
#ifdef EX_5_2
	float rad = 0.f;
	static float increment = 0.001f;
	static std::vector<Vector2> hearts;
	HSVColor hsv(0.f, 1.f, 0.85f);
	static Vector2 pivot(200.f, 0.f);

	if (hearts.empty())
	{
		for (rad = 0.f; rad < Math::TwoPI; rad += increment)
		{
			float sin = sinf(rad);
			float cos = cosf(rad);
			float cos2 = cosf(2 * rad);
			float cos3 = cosf(3 * rad);
			float cos4 = cosf(4 * rad);

			float x = 16.f * sin * sin * sin;
			float y = 13 * cos - 5 * cos2 - 2 * cos3 - cos4;

			hearts.push_back(Vector2(x, y));
		}
	}

	// S
	Vector2 sBasic1(currentScale, 0.f);
	Vector2 sBasic2(0.f, currentScale);
	Matrix2x2 sMatrix(sBasic1, sBasic2);

	// R
	float sin, cos;
	Math::GetSinCos(sin, cos, currentDegree);
	Vector2 rBasis1(cos, sin);
	Vector2 rBasis2(-sin, cos);
	Matrix2x2 rMatrix(rBasis1, rBasis2);

	// T (아핀공간이 아닌, 2차원 벡터니, x 좌표 스케일링? 이라 이해하는 게 좋을듯)
	Vector2 shBasic1 = Vector2::UnitX;
	Vector2 shBasic2(currentShear, 1.f);
	Matrix2x2 shMatrix(shBasic1, shBasic2);

	Matrix2x2 cMatrix = shMatrix * rMatrix * sMatrix;

	// Inverse S
	float invScale = 1.f / currentScale;
	Vector2 isBasis1(invScale, 0.f);
	Vector2 isBasis2(0.f, invScale);
	Matrix2x2 isMatrix(isBasis1, isBasis2);

	// Inverse R
	Matrix2x2 irMatrix = rMatrix.Transpose();

	// Inverse T (아핀공간이 아닌, 2차원 벡터니, x 좌표 스케일링? 이라 이해하는 게 좋을듯)
	Vector2 ishBasis1 = Vector2::UnitX;
	Vector2 ishBasis2(-currentShear, 1.f);
	Matrix2x2 ishMatrix(ishBasis1, ishBasis2);

	Matrix2x2 icMatrix = isMatrix * irMatrix * ishMatrix;


	rad = 0.f;
	for (Vector2 const& v : hearts)
	{
		Vector2 left = cMatrix * v;
		r.DrawPoint(left - pivot, hsv.ToLinearColor());

		Vector2 right = icMatrix * left;
		r.DrawPoint(right + pivot, hsv.ToLinearColor());

		hsv.H = rad / Math::TwoPI;
		rad += increment;

	}


#endif
}

// 메시를 그리는 함수
void SoftRenderer::DrawMesh2D(const class DD::Mesh& InMesh, const Matrix3x3& InMatrix, const LinearColor& InColor)
{
}

// 삼각형을 그리는 함수
void SoftRenderer::DrawTriangle2D(std::vector<DD::Vertex2D>& InVertices, const LinearColor& InColor, FillMode InFillMode)
{
}
#endif



















































































/*-----------------------------------------
				  PART 2
-----------------------------------------*/
#if 0 // EX_6_1__EX_7_1

// 격자를 그리는 함수
void SoftRenderer::DrawGizmo2D()
{
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	// 그리드 색상
	LinearColor gridColor(LinearColor(0.8f, 0.8f, 0.8f, 0.3f));

	// 뷰의 영역 계산
	Vector2 viewPos = g.GetMainCamera().GetTransform().GetPosition();
	Vector2 extent = Vector2(_ScreenSize.X * 0.5f, _ScreenSize.Y * 0.5f);

	// 좌측 하단에서부터 격자 그리기
	int xGridCount = _ScreenSize.X / _Grid2DUnit;
	int yGridCount = _ScreenSize.Y / _Grid2DUnit;

	// 그리드가 시작되는 좌하단 좌표 값 계산
	Vector2 minPos = viewPos - extent;
	Vector2 minGridPos = Vector2(ceilf(minPos.X / (float)_Grid2DUnit), ceilf(minPos.Y / (float)_Grid2DUnit)) * (float)_Grid2DUnit;
	ScreenPoint gridBottomLeft = ScreenPoint::ToScreenCoordinate(_ScreenSize, minGridPos - viewPos);

	for (int ix = 0; ix < xGridCount; ++ix)
	{
		r.DrawFullVerticalLine(gridBottomLeft.X + ix * _Grid2DUnit, gridColor);
	}

	for (int iy = 0; iy < yGridCount; ++iy)
	{
		r.DrawFullHorizontalLine(gridBottomLeft.Y - iy * _Grid2DUnit, gridColor);
	}

	ScreenPoint worldOrigin = ScreenPoint::ToScreenCoordinate(_ScreenSize, -viewPos);
	r.DrawFullHorizontalLine(worldOrigin.Y, LinearColor::Red);
	r.DrawFullVerticalLine(worldOrigin.X, LinearColor::Green);
}

// 게임 오브젝트 목록


// 최초 씬 로딩을 담당하는 함수
void SoftRenderer::LoadScene2D()
{
	// 최초 씬 로딩에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();

}

// 게임 로직과 렌더링 로직이 공유하는 변수
#ifdef EX_6_1
Vector2 currentPosition;
float currentScale = 10.f;
float currentDegree = 0.f;
#endif
#ifdef EX_7_1
float fovAngle = 60.f;
Vector2 playerPosition(0.f, 0.f);
LinearColor playerColor = LinearColor::Gray;
Vector2 targetPosition(0.f, 100.f);
LinearColor targetColor = LinearColor::Blue;
#endif


// 게임 로직을 담당하는 함수
void SoftRenderer::Update2D(float InDeltaSeconds)
{
	// 게임 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();
	const InputManager& input = g.GetInputManager();

	// 게임 로직의 로컬 변수
#ifdef EX_6_1
	static float moveSpeed = 100.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 180.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;

	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	currentDegree += deltaDegree;
#endif
#ifdef EX_7_1
	static float moveSpeed = 100.f;
	static std::random_device rd;
	static std::mt19937 mt(rd());
	static std::uniform_real_distribution<float> randomPosX(-300.f, 300.f);
	static std::uniform_real_distribution<float> randomPosY(-200.f, 200.f);
	static float duration = 3.f;
	static float elapsedTime = 0.f;
	static Vector2 targetStart = targetPosition;
	static Vector2 targetDestination = Vector2(randomPosX(mt), randomPosY(mt));

	static float halfFovCos = cosf(Math::Deg2Rad(fovAngle * 0.5f)); // 시야각 cos 값은 최초 1회만 계산해 보관

	elapsedTime = Math::Clamp(elapsedTime + InDeltaSeconds, 0.f, duration);

	if (elapsedTime == duration)
	{
		targetStart = targetDestination;
		targetPosition = targetDestination;
		targetDestination = Vector2(randomPosX(mt), randomPosY(mt));

		elapsedTime = 0;
	}
	else
	{
		float ratio = elapsedTime / duration;
		targetPosition = Vector2(Math::Lerp(targetStart.X, targetDestination.X, ratio),
			Math::Lerp(targetStart.Y, targetDestination.Y, ratio));
	}

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;

	Vector2 f = Vector2::UnitY;
	Vector2 v = (targetPosition - playerPosition).GetNormalize();

	if (v.Dot(f) >= halfFovCos)
	{
		playerColor = LinearColor::Red;
		targetColor = LinearColor::Red;
	}
	else
	{
		playerColor = LinearColor::Gray;
		targetColor = LinearColor::Blue;
	}

	playerPosition += deltaPosition;
#endif

}

// 렌더링 로직을 담당하는 함수
void SoftRenderer::Render2D()
{
	// 렌더링 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();


	// 배경에 격자 그리기
	DrawGizmo2D();

	// 렌더링 로직의 로컬 변수
#ifdef EX_6_1
	float rad = 0.f;
	static float increment = 0.001f;
	static std::vector<Vector2> hearts;
	HSVColor hsv(0.f, 1.f, 0.85f);


	if (hearts.empty())
	{
		for (rad = 0.f; rad < Math::TwoPI; rad += increment)
		{
			float sin = sinf(rad);
			float cos = cosf(rad);
			float cos2 = cosf(2 * rad);
			float cos3 = cosf(3 * rad);
			float cos4 = cosf(4 * rad);

			float x = 16.f * sin * sin * sin;
			float y = 13 * cos - 5 * cos2 - 2 * cos3 - cos4;

			hearts.push_back(Vector2(x, y));
		}
	}



	// S
	Vector3 sBasis1(currentScale, 0.f, 0.f);
	Vector3 sBasis2(0.f, currentScale, 0.f);
	Vector3 sBasis3(0.f, 0.f, currentScale);
	Matrix3x3 sMatrix(sBasis1, sBasis2, sBasis3);



	// R
	float sin = 0.f, cos = 0.f;
	Math::GetSinCos(sin, cos, currentDegree);
	Vector3 rBasis1(cos, sin, 0.f);
	Vector3 rBasis2(-sin, cos, 0.f);
	Vector3 rBasis3 = Vector3::UnitZ;
	Matrix3x3 rMatrix(rBasis1, rBasis2, rBasis3);



	// T (아핀공간)
	Vector3 tBasis1 = Vector3::UnitX;
	Vector3 tBasis2 = Vector3::UnitY;
	Vector3 tBasis3(currentPosition.X, currentPosition.Y, 1.f);
	Matrix3x3 tMatrix(tBasis1, tBasis2, tBasis3);



	Matrix3x3 finalMatrix = tMatrix * rMatrix * sMatrix;


	rad = 0.f;
	for (Vector2 const& v : hearts)
	{
		Vector3 newV(v.X, v.Y, 1.f); // 아핀 공간을 위해 3차벡터로 변환 ( 마지막은 아핀공간을 위해 1.f)

		Vector3 finalV = finalMatrix * newV;

		hsv.H = rad / Math::TwoPI;
		r.DrawPoint(finalV.ToVector2(), hsv.ToLinearColor());
		rad += increment;
	}
#endif
#ifdef EX_7_1
	static float radius = 5.f;
	static std::vector<Vector2> sphere;
	static float sightLength = 300.f;


	if (sphere.empty())
	{
		for (float x = -radius; x <= radius; ++x)
		{
			for (float y = -radius; y <= radius; ++y)
			{
				Vector2 pointToTest = Vector2(x, y);
				float squaredLength = pointToTest.SizeSquared();

				if (squaredLength <= radius * radius)
				{
					sphere.push_back(Vector2(x, y));
				}
			}
		}
	}



	float halfFovSin = 0.f, halfFovCos = 0.f;
	Math::GetSinCos(halfFovSin, halfFovCos, fovAngle * 0.5f);

	r.DrawLine(playerPosition, playerPosition + Vector2(sightLength * halfFovSin, sightLength * halfFovCos), playerColor);
	r.DrawLine(playerPosition, playerPosition + Vector2(-sightLength * halfFovSin, sightLength * halfFovCos), playerColor);
	r.DrawLine(playerPosition, playerPosition + Vector2::UnitY * sightLength * 0.2f, playerColor);

	for (Vector2 const& v : sphere)
	{
		r.DrawPoint(v + playerPosition, playerColor);
	}
	for (Vector2 const& v : sphere)
	{
		r.DrawPoint(v + targetPosition, targetColor);
	}
#endif

}

// 메시를 그리는 함수
void SoftRenderer::DrawMesh2D(const class DD::Mesh& InMesh, const Matrix3x3& InMatrix, const LinearColor& InColor)
{
}

// 삼각형을 그리는 함수
void SoftRenderer::DrawTriangle2D(std::vector<DD::Vertex2D>& InVertices, const LinearColor& InColor, FillMode InFillMode)
{
}
#endif


















































































/*-----------------------------------------
				  PART 3
-----------------------------------------*/
#if 0 // EX_7_2__EX_8_2

// 격자를 그리는 함수
void SoftRenderer::DrawGizmo2D()
{
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	// 그리드 색상
	LinearColor gridColor(LinearColor(0.8f, 0.8f, 0.8f, 0.3f));

	// 뷰의 영역 계산
	Vector2 viewPos = g.GetMainCamera().GetTransform().GetPosition();
	Vector2 extent = Vector2(_ScreenSize.X * 0.5f, _ScreenSize.Y * 0.5f);

	// 좌측 하단에서부터 격자 그리기
	int xGridCount = _ScreenSize.X / _Grid2DUnit;
	int yGridCount = _ScreenSize.Y / _Grid2DUnit;

	// 그리드가 시작되는 좌하단 좌표 값 계산
	Vector2 minPos = viewPos - extent;
	Vector2 minGridPos = Vector2(ceilf(minPos.X / (float)_Grid2DUnit), ceilf(minPos.Y / (float)_Grid2DUnit)) * (float)_Grid2DUnit;
	ScreenPoint gridBottomLeft = ScreenPoint::ToScreenCoordinate(_ScreenSize, minGridPos - viewPos);

	for (int ix = 0; ix < xGridCount; ++ix)
	{
		r.DrawFullVerticalLine(gridBottomLeft.X + ix * _Grid2DUnit, gridColor);
	}

	for (int iy = 0; iy < yGridCount; ++iy)
	{
		r.DrawFullHorizontalLine(gridBottomLeft.Y - iy * _Grid2DUnit, gridColor);
	}

	ScreenPoint worldOrigin = ScreenPoint::ToScreenCoordinate(_ScreenSize, -viewPos);
	r.DrawFullHorizontalLine(worldOrigin.Y, LinearColor::Red);
	r.DrawFullVerticalLine(worldOrigin.X, LinearColor::Green);
}

// 게임 오브젝트 목록


// 최초 씬 로딩을 담당하는 함수
void SoftRenderer::LoadScene2D()
{
	// 최초 씬 로딩에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();

}

// 게임 로직과 렌더링 로직이 공유하는 변수
#ifdef EX_7_2
Vector2 lightPosition;
LinearColor lightColor;
Vector2 circlePosition;
#endif
#ifdef EX_7_3
Vector2 point(0.f, 250.f);
Vector2 lineStart(-400.f, 0.f);
Vector2 lineEnd(400.f, 0.f);
#endif
#ifdef EX_8_1
Vector2 currentPosition;
float currentScale = 10.f;
float currentDegree = 0.f;
#endif
#ifdef EX_8_2
Vector2 currentPosition;
float currentScale = 10.f;
float currentDegree = 0.f;
#endif


// 게임 로직을 담당하는 함수
void SoftRenderer::Update2D(float InDeltaSeconds)
{
	// 게임 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();
	const InputManager& input = g.GetInputManager();

	// 게임 로직의 로컬 변수
#ifdef EX_7_2
	// EX_7_2 : 게임 로직의 로컬 변수
	static float duration = 20.f;
	static float elapsedTime = 0.f;
	static float currentDegree = 0.f;
	static float lightDistance = 2000.f;
	static HSVColor lightHSVColor;

	// EX_7_2 : 경과 시간에 따른 현재 각과 이를 사용한 [0,1] 값의 생성
	elapsedTime += InDeltaSeconds;
	elapsedTime = Math::FMod(elapsedTime, duration); // ※ FMod : (1) % (2) 
	float currentRad = (elapsedTime / duration) * Math::TwoPI;
	float alpha = (sinf(currentRad) + 1) * 0.5f;

	// EX_7_2 : [0,1] 을 활용해 주기적으로 크기를 반복하기
	currentDegree = Math::Lerp(0.f, 360.f, alpha);


	// EX_7_2 : 광원의 좌표와 색상
	float sin = 0.f, cos = 0.f;
	Math::GetSinCosRad(sin, cos, currentRad);
	lightPosition = Vector2(cos, sin) * lightDistance;

	lightHSVColor.H = currentRad * Math::InvPI * 0.5f; // ※ Math::InvPI : 1 / PI
	lightColor = lightHSVColor.ToLinearColor();
#endif
#ifdef EX_7_3
	static float duration = 6.f;
	static float elapsedTime = 0.f;
	static float currentDegree = 0.f;
	static float rotateSpeed = 180.f;
	static float distance = 250.f;
	static std::random_device rd;
	static std::mt19937 mt(rd());
	static std::uniform_real_distribution<float> randomY(-200.f, 200.f);

	
	elapsedTime = Math::Clamp(elapsedTime + InDeltaSeconds, 0.f, duration);
	if (elapsedTime == duration)
	{
		lineStart = Vector2(-400.f, randomY(mt));
		lineEnd = Vector2(400.f, randomY(mt));
		elapsedTime = 0.f;
	}


	// EX_7_3 : 점의 위치 결정
	currentDegree = Math::FMod(currentDegree + rotateSpeed * InDeltaSeconds, 360.f);
	float sin = 0.f, cos = 0.f;
	Math::GetSinCos(sin, cos, currentDegree);
	point = Vector2(cos, sin) * distance;
#endif
#ifdef EX_8_1
	static float moveSpeed = 30.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 100.f;


	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;


	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	currentDegree += deltaDegree;
#endif
#ifdef EX_8_2
	static float moveSpeed = 30.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 100.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;

	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	currentDegree += deltaDegree;
#endif
}

// 렌더링 로직을 담당하는 함수
void SoftRenderer::Render2D()
{
	// 렌더링 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();


	// 배경에 격자 그리기
	DrawGizmo2D();

	// 렌더링 로직의 로컬 변수
#ifdef EX_7_2
	static std::vector<Vector2> light;
	static float lightRadius = 10.f;
	static std::vector<Vector2> circle;
	static float circleRadius = 50.f;


	// EX_7_2 : 광원을 표현하는 구체 만들기
	if (light.empty())
	{
		for (float x = -lightRadius; x <= lightRadius; ++x)
		{
			for (float y = -lightRadius; y <= lightRadius; ++y)
			{
				Vector2 pointToTest = Vector2(x, y);
				float squaredLength = pointToTest.SizeSquared();

				if (squaredLength <= lightRadius * lightRadius)
				{
					light.push_back(Vector2(x, y));
				}
			}
		}
	}

	// EX_7_2 : 빛을 받는 물체 만들기
	if (circle.empty())
	{
		for (float x = -circleRadius; x <= circleRadius; ++x)
		{
			for (float y = -circleRadius; y <= circleRadius; ++y)
			{
				Vector2 pointToTest = Vector2(x, y);
				float squaredLength = pointToTest.SizeSquared();

				if (squaredLength <= circleRadius * circleRadius)
				{
					circle.push_back(Vector2(x, y));
				}
			}
		}
	}


	// EX_7_2 : 광원 그리기
	static float lightLineLength = 50.f;
	r.DrawLine(lightPosition, lightPosition - lightPosition.GetNormalize() * lightLineLength, lightColor);
	for (Vector2 const& v : light)
	{
		r.DrawPoint(v + lightPosition, lightColor);
	}



	// EX_7_2 : 광원을 받는 구체의 모든 픽셀에 NdotL 을 계산해 음영을 산출하고, 이를 최종 색상에 반영
	for (Vector2 const& v : circle)
	{
		Vector2 n = (v - circlePosition).GetNormalize();
		Vector2 l = (lightPosition - v).GetNormalize();
		float shading = Math::Clamp(n.Dot(l), 0.f, 1.f);

		r.DrawPoint(v, lightColor * shading);
	}
#endif
#ifdef EX_7_3
	static float radius = 5.f;
	static std::vector<Vector2> circle;


	if (circle.empty())
	{
		for (float x = -radius; x <= radius; ++x)
		{
			for (float y = -radius; y <= radius; ++y)
			{
				Vector2 pointToTest = Vector2(x, y);
				float squaredLength = pointToTest.SizeSquared();

				if (squaredLength <= radius * radius)
				{
					circle.push_back(Vector2(x, y));
				}
			}
		}
	}

	// EX_7_3 : 붉은색으로 점 그리기
	for (auto const& v : circle)
	{
		r.DrawPoint(v + point, LinearColor::Red);
	}


	// EX_7_3 : 투영할 라인 그리기
	r.DrawLine(lineStart, lineEnd, LinearColor::Black);
	r.DrawLine(lineStart, point, LinearColor::Red);


	// EX_7_3 : 투영된 위치와 거리 계산
	Vector2 unitV = (lineEnd - lineStart).GetNormalize();
	Vector2 u = point - lineStart;
	Vector2 projV =  unitV * unitV.Dot(u); // 투영행렬 생성.. (이 한줄 때문에 이렇게 코드 길게 썼네..)
	Vector2 projectedPoint = lineStart + projV;
	float distance = (projectedPoint - point).Size();


	// EX_7_3 : 투영된 점 그리기
	for (Vector2 const& v : circle)
	{
		r.DrawPoint(v + projectedPoint, LinearColor::Magenta);
	}


	// EX_7_3 : 투영 라인 그리기
	r.DrawLine(projectedPoint, point, LinearColor::Gray);
#endif
#ifdef EX_8_1
	// EX_8_1 : 메시 데이터의 선언
	static constexpr float squareHalSize = 2.5f;
	static constexpr size_t vertexCount = 4;
	static constexpr size_t triangleCount = 2;


	// EX_8_1 : 메시를 구성하는 정점 배열과 인덱스 배열의 생성
	static constexpr std::array<Vertex2D, vertexCount> rawVertices = {
		Vertex2D(Vector2(-squareHalSize, -squareHalSize)),
		Vertex2D(Vector2(-squareHalSize, squareHalSize)),
		Vertex2D(Vector2(squareHalSize, squareHalSize)),
		Vertex2D(Vector2(squareHalSize, -squareHalSize))
	};

	// EX_8_1 : indices 지정
	static constexpr std::array<size_t, triangleCount * 3> indices = {
		0, 1, 2,
		0, 2, 3
	};





	// S
	Vector3 sBasis1(currentScale, 0.f, 0.f);
	Vector3 sBasis2(0.f, currentScale, 0.f);
	Vector3 sBasis3(0.f, 0.f, currentScale);
	Matrix3x3 sMatrix(sBasis1, sBasis2, sBasis3);


	// R
	float sin = 0.f, cos = 0.f;
	Math::GetSinCos(sin, cos, currentDegree);
	Vector3 rBasis1(cos, sin, 0.f);
	Vector3 rBasis2(-sin, cos, 0.f);
	Vector3 rBasis3 = Vector3::UnitZ;
	Matrix3x3 rMatrix(rBasis1, rBasis2, rBasis3);



	// T
	Vector3 tBasis1 = Vector3::UnitX;
	Vector3 tBasis2 = Vector3::UnitY;
	Vector3 tBasis3(currentPosition.X, currentPosition.Y, 1.f);
	Matrix3x3 tMatrix(tBasis1, tBasis2, tBasis3);


	Matrix3x3 finalMatrix = tMatrix * rMatrix * sMatrix;


	

	// EX_8_1 : 행렬을 적용한 메시 정보를 사용해 물체를 렌더링
	static std::vector<Vertex2D> vertices(vertexCount);
	for (size_t vi = 0; vi < vertexCount; ++vi)
	{
		vertices[vi].Position = finalMatrix * rawVertices[vi].Position;
	}

	for (size_t ti = 0; ti < triangleCount; ++ti)
	{
		size_t bi = ti * 3;
		r.DrawLine(vertices[indices[bi]].Position, vertices[indices[bi + 1]].Position, _WireframeColor);
		r.DrawLine(vertices[indices[bi]].Position, vertices[indices[bi + 2]].Position, _WireframeColor);
		r.DrawLine(vertices[indices[bi + 1]].Position, vertices[indices[bi + 2]].Position, _WireframeColor);
	}
#endif
#ifdef EX_8_2
	// EX_8_2 : 메시 데이터의 선언
	static constexpr float squaredHalfSize = 2.5f;
	static constexpr size_t vertexCount = 4;
	static constexpr size_t triangleCount = 2;


	// EX_8_2 : 메시를 구성하는 정점 배열과 인덱스 배열의 생성
	static constexpr std::array<Vertex2D, vertexCount> rawVertices = {
		Vertex2D(Vector2(-squaredHalfSize, -squaredHalfSize)),
		Vertex2D(Vector2(-squaredHalfSize, squaredHalfSize)),
		Vertex2D(Vector2(squaredHalfSize, squaredHalfSize)),
		Vertex2D(Vector2(squaredHalfSize, -squaredHalfSize))
	};

	
	// EX_8_2 : indices 지정
	static constexpr std::array<size_t, triangleCount * 3> indices = {
		0, 1, 2,
		0, 2, 3
	};


	// S
	Vector3 sBasis1(currentScale, 0.f, 0.f);
	Vector3 sBasis2(0, currentScale, 0);
	Vector3 sBasis3(0, 0, currentScale);
	Matrix3x3 sMatrix(sBasis1, sBasis2, sBasis3);

	// R
	float sin = 0.f, cos = 0.f;
	Math::GetSinCos(sin, cos, currentDegree);
	Vector3 rBasis1(cos, sin, 0);
	Vector3 rBasis2(-sin, cos, 0);
	Vector3 rBasis3 = Vector3::UnitZ;
	Matrix3x3 rMatrix(rBasis1, rBasis2, rBasis3);


	// T
	Vector3 tBasis1 = Vector3::UnitX;
	Vector3 tBasis2 = Vector3::UnitY;
	Vector3 tBasis3(currentPosition.X, currentPosition.Y, 1);
	Matrix3x3 tMatrix(tBasis1, tBasis2, tBasis3);

	Matrix3x3 finalMatrix = tMatrix * rMatrix * sMatrix;


	// EX_8_2 : 행렬을 적용한 메시 정보를 사용해 물체를 렌더링
	static std::vector<Vertex2D> vertices(vertexCount);
	for (size_t vi = 0; vi < vertexCount; ++vi)
	{
		vertices[vi].Position = finalMatrix * rawVertices[vi].Position;
	}


	// EX_8_2 : 변화된 정점을 잇는 선 그리기
	for (size_t ti = 0; ti < triangleCount; ++ti)
	{
		size_t bi = ti * 3;
		std::array<Vertex2D, 3> tv = { vertices[indices[bi]], vertices[indices[bi + 1]], vertices[indices[bi + 2]] };

		Vector2 minPos(Math::Min3(tv[0].Position.X, tv[1].Position.X, tv[2].Position.X),
			Math::Min3(tv[0].Position.Y, tv[1].Position.Y, tv[2].Position.Y));
		Vector2 maxPos(Math::Max3(tv[0].Position.X, tv[1].Position.X, tv[2].Position.X),
			Math::Max3(tv[0].Position.Y, tv[1].Position.Y, tv[2].Position.Y));


		// EX_8_2 : 무게중심좌표를 위한 준비작업
		Vector2 u = tv[1].Position - tv[0].Position;
		Vector2 v = tv[2].Position - tv[0].Position;


		// EX_8_2 : 공통 분모 (uv * uv - uu * vv)
		float udotv = u.Dot(v);
		float vdotv = v.Dot(v);
		float udotu = u.Dot(u);
		float denominator = udotv * udotv - vdotv * udotu;


		// EX_8_2 : 퇴화삼각형은 그리지 않음
		if (denominator == 0.f)
		{
			continue;
		}

		float invDenominator = 1.f / denominator;

		// EX_8_2 : 화면상의 점 구하기
		ScreenPoint lowerLeftPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, minPos);
		ScreenPoint upperRightPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, maxPos);

		// EX_8_2 : 두 점이 화면 밖을 벗어나는 경우 클리핑 처리
		lowerLeftPoint.X = Math::Max(0, lowerLeftPoint.X);
		lowerLeftPoint.Y = Math::Min(_ScreenSize.Y, lowerLeftPoint.Y);
		upperRightPoint.X = Math::Min(_ScreenSize.X, upperRightPoint.X);
		upperRightPoint.Y = Math::Max(0, upperRightPoint.Y);


		// EX_8_2 : 삼각형을 둘러싼 사각형 영역의 픽셀을 모두 순회
		for (int x = lowerLeftPoint.X; x <= upperRightPoint.X; ++x)
		{
			for (int y = upperRightPoint.Y; y <= lowerLeftPoint.Y; ++y)
			{
				ScreenPoint fragment = ScreenPoint(x, y);
				Vector2 pointToTest = fragment.ToCartesianCoordinate(_ScreenSize);
				Vector2 w = pointToTest - tv[0].Position;

				float wdotu = w.Dot(u);
				float wdotv = w.Dot(v);

				// EX_8_2 : 분자 값을 구하고 최종 무게중심좌표 산출
				float s = (wdotv * udotv - wdotu * vdotv) * invDenominator;
				float t = (wdotu * udotv - wdotv * udotu) * invDenominator;
				float oneMinusST = 1.f - s - t;

				// EX_8_2 : 컨벡스 조건을 만족할 때만 점 찍기
				if (((s >= 0.f) && (s <= 1.f)) && ((t >= 0.f) && (t <= 1.f)) && ((oneMinusST >= 0.f) && (oneMinusST <= 1.f)))
				{
					r.DrawPoint(fragment, LinearColor::Blue);
				}
			}
		}
	}
	


#endif

}

// 메시를 그리는 함수
void SoftRenderer::DrawMesh2D(const class DD::Mesh& InMesh, const Matrix3x3& InMatrix, const LinearColor& InColor)
{
}

// 삼각형을 그리는 함수
void SoftRenderer::DrawTriangle2D(std::vector<DD::Vertex2D>& InVertices, const LinearColor& InColor, FillMode InFillMode)
{
}
#endif // EX_7_2__EX_8_2






































































































/*-----------------------------------------
				  PART 4
-----------------------------------------*/
#if 1 // EX_8_3__

// 격자를 그리는 함수
void SoftRenderer::DrawGizmo2D()
{
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	// 그리드 색상
	LinearColor gridColor(LinearColor(0.8f, 0.8f, 0.8f, 0.3f));

	// 뷰의 영역 계산
	Vector2 viewPos = g.GetMainCamera().GetTransform().GetPosition();
	Vector2 extent = Vector2(_ScreenSize.X * 0.5f, _ScreenSize.Y * 0.5f);

	// 좌측 하단에서부터 격자 그리기
	int xGridCount = _ScreenSize.X / _Grid2DUnit;
	int yGridCount = _ScreenSize.Y / _Grid2DUnit;

	// 그리드가 시작되는 좌하단 좌표 값 계산
	Vector2 minPos = viewPos - extent;
	Vector2 minGridPos = Vector2(ceilf(minPos.X / (float)_Grid2DUnit), ceilf(minPos.Y / (float)_Grid2DUnit)) * (float)_Grid2DUnit;
	ScreenPoint gridBottomLeft = ScreenPoint::ToScreenCoordinate(_ScreenSize, minGridPos - viewPos);

	for (int ix = 0; ix < xGridCount; ++ix)
	{
		r.DrawFullVerticalLine(gridBottomLeft.X + ix * _Grid2DUnit, gridColor);
	}

	for (int iy = 0; iy < yGridCount; ++iy)
	{
		r.DrawFullHorizontalLine(gridBottomLeft.Y - iy * _Grid2DUnit, gridColor);
	}

	ScreenPoint worldOrigin = ScreenPoint::ToScreenCoordinate(_ScreenSize, -viewPos);
	r.DrawFullHorizontalLine(worldOrigin.Y, LinearColor::Red);
	r.DrawFullVerticalLine(worldOrigin.X, LinearColor::Green);
}

// 게임 오브젝트 목록


// 최초 씬 로딩을 담당하는 함수
void SoftRenderer::LoadScene2D()
{
	// 최초 씬 로딩에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();

}

// 게임 로직과 렌더링 로직이 공유하는 변수
#ifdef EX_8_3
Vector2 currentPosition;
float currentScale = 10.f;
float currentDegree = 0.f;
#endif
#ifdef EX_8_4
Vector2 currentPosition;
float currentScale = 10.f;
float currentDegree = 0.f;
#endif


// 게임 로직을 담당하는 함수
void SoftRenderer::Update2D(float InDeltaSeconds)
{
	// 게임 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();
	const InputManager& input = g.GetInputManager();

	// 게임 로직의 로컬 변수
#ifdef EX_8_3
	static float moveSpeed = 30.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 100.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;

	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	currentDegree += deltaDegree;
#endif
#ifdef EX_8_4
	static float moveSpeed = 30.f;
	static float scaleMin = 5.f;
	static float scaleMax = 20.f;
	static float scaleSpeed = 20.f;
	static float rotateSpeed = 100.f;

	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;
	float deltaScale = input.GetAxis(InputAxis::ZAxis) * scaleSpeed * InDeltaSeconds;
	float deltaDegree = input.GetAxis(InputAxis::WAxis) * rotateSpeed * InDeltaSeconds;

	currentPosition += deltaPosition;
	currentScale = Math::Clamp(currentScale + deltaScale, scaleMin, scaleMax);
	currentDegree += deltaDegree;
#endif

}

// 렌더링 로직을 담당하는 함수
void SoftRenderer::Render2D()
{
	// 렌더링 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();


	// 배경에 격자 그리기
	DrawGizmo2D();

	// 렌더링 로직의 로컬 변수
#ifdef EX_8_3
	// EX_8_3 : 메시 데이터 선언
	static constexpr size_t vertexCount = 3;
	static constexpr size_t triangleCount = 1;

	// EX_8_3 : 메시를 구성하는 정점 배열과 인덱스 배열의 생성
	static constexpr std::array<Vertex2D, vertexCount> rawVerticies = {
		Vertex2D(Vector2(0.f, 2.5f), LinearColor(1, 0, 0)),
		Vertex2D(Vector2(-5.f, -2.5f), LinearColor(0, 1, 0)),
		Vertex2D(Vector2(5.f, -2.5f), LinearColor(0, 0, 1))
	};

	static constexpr std::array<size_t, triangleCount * 3> indices = {
		0, 2, 1
	};


	// S
	Vector3 sBasis1(currentScale, 0, 0);
	Vector3 sBasis2(0, currentScale, 0);
	Vector3 sBasis3(0, 0, currentScale);
	Matrix3x3 sMatrix(sBasis1, sBasis2, sBasis3);

	// R
	float sin = 0.f, cos = 0.f;
	Math::GetSinCos(sin, cos, currentDegree);
	Vector3 rBasis1(cos, sin, 0);
	Vector3 rBasis2(-sin, cos, 0);
	Vector3 rBasis3 = Vector3::UnitZ;
	Matrix3x3 rMatrix(rBasis1, rBasis2, rBasis3);

	// T
	Vector3 tBasis1 = Vector3::UnitX;
	Vector3 tBasis2 = Vector3::UnitY;
	Vector3 tBasis3(currentPosition.X, currentPosition.Y, 1);
	Matrix3x3 tMatrix(tBasis1, tBasis2, tBasis3);

	Matrix3x3 finalMatrix = tMatrix * rMatrix * sMatrix;


	// EX_8_3 : 행렬을 적용한 메시 정보를 사용해 물체를 렌더링
	static std::vector<Vertex2D> verticies(vertexCount);
	for (size_t vi = 0; vi < vertexCount; ++vi)
	{
		verticies[vi].Position = finalMatrix * rawVerticies[vi].Position;
		verticies[vi].Color = rawVerticies[vi].Color;
	}
	

	// EX_8_3 : 변환된 정점을 채우는 선 그리기
	for (size_t ti = 0; ti < triangleCount; ++ti)
	{
		size_t bi = ti * 3;
		std::array<Vertex2D, 3> tv = { verticies[indices[bi]], verticies[indices[bi + 1]], verticies[indices[bi + 2]] };

		Vector2 minPos(Math::Min3(tv[0].Position.X, tv[1].Position.X, tv[2].Position.X),
			Math::Min3(tv[0].Position.Y, tv[1].Position.Y, tv[2].Position.Y));
		Vector2 maxPos(Math::Max3(tv[0].Position.X, tv[1].Position.X, tv[2].Position.X),
			Math::Max3(tv[0].Position.Y, tv[1].Position.Y, tv[2].Position.Y));

		// EX_8_3 : 무게중심좌표를 위한 준비작업
		Vector2 u = tv[1].Position - tv[0].Position;
		Vector2 v = tv[2].Position - tv[0].Position;

		// EX_8_3 : 공통 분모 (uv * uv - uu * vv)
		float udotv = u.Dot(v);
		float vdotv = v.Dot(v);
		float udotu = u.Dot(u);
		float denominator = udotv * udotv - vdotv * udotu;


		// EX_8_3 : 퇴화삼각형은 그리지 않음
		if (denominator == 0.f)
		{
			continue;
		}

		float invDenominator = 1.f / denominator;

		// EX_8_3 : 화면상의 점 구하기
		ScreenPoint lowerLeftPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, minPos);
		ScreenPoint upperRightPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, maxPos);


		// EX_8_3 : 두 점이 화면 밖을 벗어나는 경우 클리핑 처리
		lowerLeftPoint.X = Math::Max(0, lowerLeftPoint.X);
		lowerLeftPoint.Y = Math::Min(_ScreenSize.Y, lowerLeftPoint.Y);
		upperRightPoint.X = Math::Min(_ScreenSize.X, upperRightPoint.X);
		upperRightPoint.Y = Math::Max(0, upperRightPoint.Y);


		// EX_8_3 : 삼각형을 둘러싼 사각형 영역의 픽셀을 모두 순회
		for (int x = lowerLeftPoint.X; x <= upperRightPoint.X; ++x)
		{
			for (int y = upperRightPoint.Y; y <= lowerLeftPoint.Y; ++y)
			{
				ScreenPoint fragment = ScreenPoint(x, y);
				Vector2 pointToTest = fragment.ToCartesianCoordinate(_ScreenSize);
				Vector2 w = pointToTest - tv[0].Position;


				float wdotu = w.Dot(u);
				float wdotv = w.Dot(v);

				// EX_8_3 : 분자 값을 구하고 최종 무게중심좌표 산출
				float s = (wdotv * udotv - wdotu * vdotv) * invDenominator;
				float t = (wdotu * udotv - wdotv * udotu) * invDenominator;
				float oneMinusST = 1.f - s - t;

				// EX_8_3 : 컨벡스 조건을 만족할 때만 점 찍기
				if ((s >= 0.f && s <= 1.f) && (t >= 0.f && t <= 1.f) && (oneMinusST >= 0.f && oneMinusST <= 1.f))
				{
					LinearColor outColor = tv[0].Color * oneMinusST + tv[1].Color * s + tv[2].Color * t; 
					// ※ S, T (1-S-T) 를 Vertex2D의 컬러값들과 선형결합!
					r.DrawPoint(fragment, outColor);
				}
			}
		}
	}
#endif
#ifdef EX_8_4

	// EX_8_4 :텍스쳐 가져오기
	const auto& texture = g.GetTexture(GameEngine::BaseTexture);


	// EX_8_4 : 메시 데이터 선언
	static constexpr float squaredHalfSize = 3.f;
	static constexpr size_t vertexCount = 4;
	static constexpr size_t triangleCount = 2;

	// EX_8_4 : 메시를 구성하는 정점 배열과 인덱스 배열의 생성
	static constexpr std::array<Vertex2D, vertexCount> rawVerticies = {
		Vertex2D(Vector2(-squaredHalfSize, -squaredHalfSize), LinearColor(), Vector2(0.125f, 0.75f)),
		Vertex2D(Vector2(squaredHalfSize, -squaredHalfSize), LinearColor(), Vector2(0.125f, 0.875f)),
		Vertex2D(Vector2(squaredHalfSize, squaredHalfSize), LinearColor(), Vector2(0.25f, 0.875f)),
		Vertex2D(Vector2(-squaredHalfSize, squaredHalfSize), LinearColor(), Vector2(0.25f, 0.75f))

		// ※ 미리 준비된 UV 텍스쳐의, 그릴 좌표를 (3)항에 입력함. 교재 286 p 참조 
	};

	// EX_8_4 : indices 지정
	static constexpr std::array<size_t, triangleCount * 3> indices = {
		0, 1, 2,
		0, 2, 3
	};


	// S
	Vector3 sBasis1(currentScale, 0, 0);
	Vector3 sBasis2(0, currentScale, 0);
	Vector3 sBasis3(0, 0, currentScale);
	Matrix3x3 sMatrix(sBasis1, sBasis2, sBasis3);

	// R
	float cos, sin;
	Math::GetSinCos(sin, cos, currentDegree);
	Vector3 rBasis1(cos, sin, 0);
	Vector3 rBasis2(-sin, cos, 0);
	Vector3 rBasis3 = Vector3::UnitZ;
	Matrix3x3 rMatrix(rBasis1, rBasis2, rBasis3);


	// T
	Vector3 tBasis1 = Vector3::UnitX;
	Vector3 tBasis2 = Vector3::UnitY;
	Vector3 tBasis3(currentPosition.X, currentPosition.Y, 1);
	Matrix3x3 tMatrix(tBasis1, tBasis2, tBasis3);

	Matrix3x3 finalMatrix = tMatrix * rMatrix * sMatrix;


	// EX_8_4 : 행렬을 적용한 메시 정보를 사용해 물체를 렌더링
	static std::vector<Vertex2D> vertices(vertexCount);
	for (size_t vi = 0; vi < vertexCount; ++vi)
	{
		vertices[vi].Position = finalMatrix * rawVerticies[vi].Position;
		vertices[vi].UV = rawVerticies[vi].UV;
	}

	// EX_8_4 : 변환된 정점을 채우는 선 그리기
	for (size_t ti = 0; ti < triangleCount; ++ti)
	{
		size_t bi = ti * 3;
		std::array<Vertex2D, 3> tv = { vertices[indices[bi]], vertices[indices[bi + 1]], vertices[indices[bi + 2]] };

		Vector2 minPos(Math::Min3(tv[0].Position.X, tv[1].Position.X, tv[2].Position.X),
			Math::Min3(tv[0].Position.Y, tv[1].Position.Y, tv[2].Position.Y));
		Vector2 maxPos(Math::Max3(tv[0].Position.X, tv[1].Position.X, tv[2].Position.X),
			Math::Max3(tv[0].Position.Y, tv[1].Position.Y, tv[2].Position.Y));

		// EX_8_4 : 무게중심좌표를 위한 준비작업
		Vector2 u = tv[1].Position - tv[0].Position;
		Vector2 v = tv[2].Position - tv[0].Position;

		// EX_8_4 : 공통 분모 (uv * vu - uu * vv)
		float udotv = u.Dot(v);
		float vdotv = v.Dot(v);
		float udotu = u.Dot(u);
		float denominator = udotv * udotv - udotu * vdotv;


		// EX_8_4 : 퇴화삼각형은 그리지 않음
		if (denominator == 0.f)
		{
			continue;
		}

		float invDenominator = 1.f / denominator;


		// EX 8_4 : 화면상의 점 구하기
		ScreenPoint lowerLeftPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, minPos);
		ScreenPoint upperRightPoint = ScreenPoint::ToScreenCoordinate(_ScreenSize, maxPos);

		// EX_8_4 : 두 점이 화면 밖을 벗어나는 경우 클리핑 처리
		lowerLeftPoint.X = Math::Max(0, lowerLeftPoint.X);
		lowerLeftPoint.Y = Math::Min(_ScreenSize.Y, lowerLeftPoint.Y);
		upperRightPoint.X = Math::Min(_ScreenSize.X, upperRightPoint.X);
		upperRightPoint.Y = Math::Max(0, upperRightPoint.Y);

		// EX_8_4 : 삼각형을 둘러싼 사각형 영역의 픽셀을 모두 순회
		for (int x = lowerLeftPoint.X; x <= upperRightPoint.X; ++x)
		{
			for (int y = upperRightPoint.Y; y <= lowerLeftPoint.Y; ++y)
			{
				ScreenPoint fragment = ScreenPoint(x, y);
				Vector2 pointToTest = fragment.ToCartesianCoordinate(_ScreenSize);
				Vector2 w = pointToTest - tv[0].Position;

				float wdotu = w.Dot(u);
				float wdotv = w.Dot(v);

				// EX_8_4 : 분자 값을 구하고 최종 무게중심좌표 산출
				float s = (wdotv * udotv - wdotu * vdotv) * invDenominator;
				float t = (wdotu * udotv - wdotv * udotu) * invDenominator;
				float oneMinusST = 1.f - s - t;

				// EX_8_4 : 컨벡스 조건을 만족할 때만 점 찍기
				if ((s >= 0.f && s <= 1.f) && (t >= 0.f && t <= 1.f) && (oneMinusST >= 0.f && oneMinusST <= 1.f))
				{
					Vector2 targetUV = tv[0].UV * oneMinusST + tv[1].UV * s + tv[2].UV * t;
					r.DrawPoint(fragment, texture.GetSample(targetUV));
				}
			}
		}
	}


#endif


}

// 메시를 그리는 함수
void SoftRenderer::DrawMesh2D(const class DD::Mesh& InMesh, const Matrix3x3& InMatrix, const LinearColor& InColor)
{
}

// 삼각형을 그리는 함수
void SoftRenderer::DrawTriangle2D(std::vector<DD::Vertex2D>& InVertices, const LinearColor& InColor, FillMode InFillMode)
{
}
#endif // EX_8_3__

