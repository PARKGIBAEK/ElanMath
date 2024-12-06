#pragma once
#include "Helper.h"
#include "Vector2D.h"

template <Numeric T>
class Point2D
{
public:
    T x, y;

    /** 세 점(a,b,c)이 주어졌을 때 벡터 ab와 ac의 외적을 구한다.<br/>
     * 외적값의 부호에 따라 점c가 점a를 기준으로 점b의 반시계 방향(Counter Clock Wise)인지 확인
    - 외적값 > 0 : 점 c가 점 a를 기준으로 점 b의 반시계 방향에 있음 
    - 외적값 < 0 : 점 c가 점 a를 기준으로 점 b의 시계 방향에 있음
    - 외적값 = 0 : 점 a,b,c가 일직선상에 있음
    */
    static T Cross(const Point2D<T>& a, const Point2D<T>& b, const Point2D<T>& c)
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }


    /** 두 벡터 v1, v2가 주어졌을 때, 벡터 v1과 v2의 외적 값을 반환
    - 반환값 > 0: 벡터 v2가 벡터 v1보다 반시계 방향에 있습니다.
    - 반환값 < 0: 벡터 v2가 벡터 v1보다 시계 방향에 있습니다.
    - 반환값 = 0: 벡터 v1과 v2가 동일한 선상에 있습니다.*/
    static T Cross(const Vector2D<T>& v1, const Vector2D<T>& v2)
    {
        const T crossProduct = v1.x * v2.y - v1.y * v2.x;
        return crossProduct;
    }
};
