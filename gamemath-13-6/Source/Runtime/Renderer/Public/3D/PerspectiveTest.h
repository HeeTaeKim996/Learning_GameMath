
#pragma once

namespace CK
{
namespace DDD
{

#if 0 // 원본
struct PerspectiveTest
{
	std::function<bool(const Vertex3D& InVertex)> ClippingTestFunc;
	std::function<Vertex3D(const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)> GetEdgeVertexFunc;
	std::array<bool, 3> TestResult;

	void ClipTriangles(std::vector<Vertex3D>& InOutVertices)
	{
		size_t triangles = InOutVertices.size() / 3;
		for (size_t ti = 0; ti < triangles; ++ti)
		{
			size_t startIndex = ti * 3;
			size_t nonPassCount = 0;

			for (size_t ix = 0; ix < 3; ++ix)
			{
				TestResult[ix] = ClippingTestFunc(InOutVertices[startIndex + ix]);
				if (TestResult[ix])
				{
					nonPassCount++;
				}
			}

			if (nonPassCount == 0)
			{
				continue;
			}
			else if (nonPassCount == 1)
			{
				DivideIntoTwoTriangles(InOutVertices, startIndex, nonPassCount);
			}
			else if (nonPassCount == 2)
			{
				ClipTriangle(InOutVertices, startIndex, nonPassCount);
			}
			else
			{
				InOutVertices.erase(InOutVertices.begin() + startIndex, InOutVertices.begin() + startIndex + 3);
				triangles--;
				ti--;
			}
		}
	}

private:
	// 점 하나가 평면의 바깥에 있어 삼각형이 2개로 쪼개지는 경우
	void DivideIntoTwoTriangles(std::vector<Vertex3D>& InOutVertices, size_t StartIndex, size_t NonPassCount)
	{
		// 평면의 바깥에 위치한 점 찾기
		BYTE index = 0; 
		if (!TestResult[0])
		{
			index = TestResult[1] ? 1 : 2;
		}

		size_t v1Index = StartIndex + (index + 1) % 3;
		size_t v2Index = StartIndex + (index + 2) % 3;
		Vertex3D v1 = InOutVertices[v1Index];
		Vertex3D v2 = InOutVertices[v2Index];
		Vertex3D clipped1 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v1);
		Vertex3D clipped2 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v2);
		InOutVertices[StartIndex] = clipped1;
		InOutVertices[StartIndex + 1] = v1;
		InOutVertices[StartIndex + 2] = v2;
		InOutVertices.push_back(clipped1);
		InOutVertices.push_back(v2);
		InOutVertices.push_back(clipped2);
	}

	// 점 두 개가 평면의 바깥에 있어 삼각형의 두 점이 변하는 경우
	void ClipTriangle(std::vector<Vertex3D>& InOutVertices, size_t StartIndex, size_t NonPassCount)
	{
		// 평면의 안쪽에 위치한 점 찾기
		BYTE index = 0;
		if (TestResult[0])
		{
			index = !TestResult[1] ? 1 : 2;
		}

		size_t v1Index = StartIndex + (index + 1) % 3;
		size_t v2Index = StartIndex + (index + 2) % 3;
		Vertex3D v1 = InOutVertices[v1Index];
		Vertex3D v2 = InOutVertices[v2Index];
		Vertex3D clipped1 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v1);
		Vertex3D clipped2 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v2);
		InOutVertices[v1Index] = clipped1;
		InOutVertices[v2Index] = clipped2;
	}
};


static auto TestFuncW0 = [](const Vertex3D& InVertex) {
	return InVertex.Position.W < 0.f;
};

static auto EdgeFuncW0 = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex) {
	float p1 = InStartVertex.Position.W;
	float p2 = InEndVertex.Position.W;
	float t = p1 / (p1 - p2);
	return InStartVertex * (1.f - t) + InEndVertex * t;
};

static auto TestFuncNY = [](const Vertex3D& InVertex) {
	return InVertex.Position.Y < -InVertex.Position.W;
};

static auto EdgeFuncNY = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex) {
	float p1 = InStartVertex.Position.W + InStartVertex.Position.Y;
	float p2 = InEndVertex.Position.W + InEndVertex.Position.Y;
	float t = p1 / (p1 - p2);
	return InStartVertex * (1.f - t) + InEndVertex * t;
};

static auto TestFuncPY = [](const Vertex3D& InVertex) {
	return InVertex.Position.Y > InVertex.Position.W;
};

static auto EdgeFuncPY = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex) {
	float p1 = InStartVertex.Position.W - InStartVertex.Position.Y;
	float p2 = InEndVertex.Position.W - InEndVertex.Position.Y;
	float t = p1 / (p1 - p2);
	return InStartVertex * (1.f - t) + InEndVertex * t;
};

static auto TestFuncNX = [](const Vertex3D& InVertex) {
	return InVertex.Position.X < -InVertex.Position.W;
};

static auto EdgeFuncNX = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex) {
	float p1 = InStartVertex.Position.W + InStartVertex.Position.X;
	float p2 = InEndVertex.Position.W + InEndVertex.Position.X;
	float t = p1 / (p1 - p2);
	return InStartVertex * (1.f - t) + InEndVertex * t;
};

static auto TestFuncPX = [](const Vertex3D& InVertex) {
	return InVertex.Position.X > InVertex.Position.W;
};

static auto EdgeFuncPX = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex) {
	float p1 = InStartVertex.Position.W - InStartVertex.Position.X;
	float p2 = InEndVertex.Position.W - InEndVertex.Position.X;
	float t = p1 / (p1 - p2);
	return InStartVertex * (1.f - t) + InEndVertex * t;
};

static auto TestFuncFar = [](const Vertex3D& InVertex) {
	return InVertex.Position.Z > InVertex.Position.W;
};

static auto EdgeFuncFar = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex) {
	float p1 = InStartVertex.Position.W - InStartVertex.Position.Z;
	float p2 = InEndVertex.Position.W - InEndVertex.Position.Z;
	float t = p1 / (p1 - p2);
	return InStartVertex * (1.f - t) + InEndVertex * t;
};

static auto TestFuncNear = [](const Vertex3D& InVertex) {
	return InVertex.Position.Z < -InVertex.Position.W;
};

static auto EdgeFuncNear = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex) {
	float p1 = InStartVertex.Position.W + InStartVertex.Position.Z;
	float p2 = InEndVertex.Position.W + InEndVertex.Position.Z;
	float t = p1 / (p1 - p2);
	return InStartVertex * (1.f - t) + InEndVertex * t;
};
#endif // 원본











































































#if 1 // 공부
struct PerspectiveTest
{
	std::function<bool(const Vertex3D& InVertex)> ClippingTestFunc;
	std::function<Vertex3D(const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)> GetEdgeVertexFunc;
	std::array<bool, 3> TestResult;

	void ClipTriangles(std::vector<Vertex3D>& InOutVertices)
	{
		size_t triangles = InOutVertices.size() / 3;
		for (size_t ti = 0; ti < triangles; ti++)
		{
			size_t startIndex = ti * 3;
			size_t nonPassCount = 0;

			for (size_t ix = 0; ix < 3; ix++)
			{
				TestResult[ix] = ClippingTestFunc(InOutVertices[startIndex + ix]);
				if (TestResult[ix])
				{
					nonPassCount++;
				}
			}

			if (nonPassCount == 0)
			{
				continue;
			}
			else if (nonPassCount == 1) // 이탈점이 하나면, 삼각형을 2개로 나누며 클리핑
			{
				DivideIntoTwoTriangles(InOutVertices, startIndex, nonPassCount);
			}
			else if (nonPassCount == 2) // 이탈점이 2개면, 1개 유지하면서 삼각형 클리핑
			{
				ClipTriangle(InOutVertices, startIndex, nonPassCount);
			}
			else
			{ // 삼각형 삭제
				InOutVertices.erase(InOutVertices.begin() + startIndex, InOutVertices.begin() + startIndex + 3);
				triangles--;
				ti--;
			}
		}
	}

private:
	void DivideIntoTwoTriangles(std::vector<Vertex3D>& InOutVertices, size_t StartIndex, size_t NonPassCount)
	{
		// 평면의 바깥에 위치한 점 찾기
		BYTE index = 0;
		if (!TestResult[0])
		{
			index = TestResult[1] ? 1 : 2;
		}


		size_t v1Index = StartIndex + (index + 1) % 3;
		size_t v2Index = StartIndex + (index + 2) % 3;
		Vertex3D v1 = InOutVertices[v1Index];
		Vertex3D v2 = InOutVertices[v2Index];

		Vertex3D clipped1 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v1);
		Vertex3D clipped2 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v2);
		/* ○ GetEdgeVertexFuc
			- 하단에 람다식으로 처리한 함수들. 아래 함수들을 보면 알 수 있듯이, 0 < t < 1 을 구해 선형보간하는데,
			  선형보간의 결과는 포지션 뿐만 아닌, UV, 컬러들도 포함됨을 알 수 있다!
		
		*/



		// 기존 InOutVertices 벡터 위치에 삼각형 1 점 수정한 것 입력
		InOutVertices[StartIndex] = clipped1;
		InOutVertices[StartIndex + 1] = v1;
		InOutVertices[StartIndex + 2] = v2;


		// 삼각형 2 는 벡터에 추가
		InOutVertices.push_back(clipped1);
		InOutVertices.push_back(v2);
		InOutVertices.push_back(clipped2);

		// ※ 나눠진 삼각형 추가할 때 순서 주의. 기존의 반시계 순서를 유지하기 위해, 새로 만들어진 두 삼각형도
		//   입력할 때 반시계 순서를 유지하도록 입력
	}


	void ClipTriangle(std::vector<Vertex3D>& InOutVertices, size_t StartIndex, size_t NonPassCount)
	{
		// 평면의 안쪽에 위치한 점 찾기 (※ 위의 함수와는 반대로 FALSE 인 index 찾기..)
		BYTE index = 0;
		if (TestResult[0])
		{
			index = !TestResult[1] ? 1 : 2;
		}

		size_t v1Index = StartIndex + (index + 1) % 3;
		size_t v2Index = StartIndex + (index + 2) % 3;
		Vertex3D v1 = InOutVertices[v1Index];
		Vertex3D v2 = InOutVertices[v2Index];

		Vertex3D clipped1 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v1);
		Vertex3D clipped2 = GetEdgeVertexFunc(InOutVertices[StartIndex + index], v2);

		InOutVertices[v1Index] = clipped1;
		InOutVertices[v2Index] = clipped2;
	}
};








static auto TestFuncW0 = [](const Vertex3D& InVertex)
	{
		return InVertex.Position.W < 0.f;
	};
static auto EdgeFuncW0 = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)
	{
		float p1 = InStartVertex.Position.W;
		float p2 = InEndVertex.Position.W;
		float t = p1 / (p1 - p2);
		return InStartVertex * (1.f - t) + InEndVertex * t;
	};


static auto TestFuncNY = [](const Vertex3D& InVertex)
	{
		return InVertex.Position.Y < -InVertex.Position.W;
	};
static auto EdgeFuncNY = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)
	{
		float p1 = InStartVertex.Position.W + InStartVertex.Position.Y;
		float p2 = InEndVertex.Position.W + InEndVertex.Position.Y;
		float t = p1 / (p1 - p2);
		return InStartVertex * (1.f - t) + InEndVertex * t;
	};

static auto TestFuncPY = [](const Vertex3D& InVertex)
	{
		return InVertex.Position.Y > InVertex.Position.W;
	};
static auto EdgeFuncPY = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)
	{
		float p1 = InStartVertex.Position.W - InStartVertex.Position.Y;
		float p2 = InEndVertex.Position.W - InEndVertex.Position.Y;
		float t = p1 / (p1 - p2);
		return InStartVertex * (1.f - t) + InEndVertex * t;
	};


static auto TestFuncNX = [](const Vertex3D& InVertex)
	{
		return InVertex.Position.X < -InVertex.Position.W;
	};
static auto EdgeFuncNX = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)
	{
		float p1 = InStartVertex.Position.W + InStartVertex.Position.X;
		float p2 = InEndVertex.Position.W + InEndVertex.Position.X;
		float t = p1 / (p1 - p2);
		return InStartVertex * (1.f - t) + InEndVertex * t;
	};

static auto TestFuncPX = [](const Vertex3D& InVertex)
	{
		return InVertex.Position.X > InVertex.Position.W;
	};
static auto EdgeFuncPX = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)
	{
		float p1 = InStartVertex.Position.W - InStartVertex.Position.X;
		float p2 = InEndVertex.Position.W - InEndVertex.Position.X;
		float t = p1 / (p1 - p2);
		return InStartVertex * (1.f - t) + InEndVertex * t;
	};


static auto TestFuncFar = [](const Vertex3D& InVertex)
	{
		return InVertex.Position.Z > InVertex.Position.W;
	};
static auto EdgeFuncFar = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)
	{
		float p1 = InStartVertex.Position.W - InStartVertex.Position.Z;
		float p2 = InEndVertex.Position.W - InEndVertex.Position.Z;
		float t = p1 / (p1 - p2);
		return InStartVertex * (1.f - t) + InEndVertex * t;
	};

static auto TestFuncNear = [](const Vertex3D& InVertex)
	{
		return InVertex.Position.Z < -InVertex.Position.W;
	};
static auto EdgeFuncNear = [](const Vertex3D& InStartVertex, const Vertex3D& InEndVertex)
	{
		float p1 = InStartVertex.Position.W + InStartVertex.Position.Z;
		float p2 = InEndVertex.Position.W + InEndVertex.Position.Z;
		float t = p1 / (p1 - p2);
		return InStartVertex * (1.f - t) + InEndVertex * t;
	};
#endif // 공부
}
}