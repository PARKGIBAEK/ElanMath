#pragma once
#include <cmath>
#include "Helper.h"
#include "Point2D.h"


template <Numeric T>
class Vector2D
{
public:
    T x, y;

    explicit Vector2D(T _x = 0, T _y = 0): x(_x), y(_y) { }
    explicit Vector2D(Point2D<T> _a): x(_a.x), y(_a.y) { }
    explicit Vector2D(Point2D<T> _o = 0, Point2D<T> _a = 0): x(_a.x - _o.x), y(_a.y - _o.y) { }

    bool operator==(const Vector2D& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vector2D& other) const { return !(this == other); }
    bool operator<(const Vector2D& other) const { return x != other.x ? x < other.x : y < other.y; }
 
    Vector2D operator +(const Vector2D& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2D operator -(const Vector2D& other) const { return Vector2(x - other.x, y - other.y); }
    Vector2D operator *(const T other) const { return Vector2(x * other, y * other); }

    /** <pre>
     * 벡터는 크기(Magnitude)와 방향(Direction)을 가지는 수학적 객체이다.
     * 크기(Magnitude)는 피타고라스 정리를 이용한 유클리디언 거리를 의미한다.
     2차원 벡터의 크기 = √(x^2+y^2)
      
     * 방향은 단위 벡터(Unit vector)라고 표현하며,
     * 벡터의 각 성분을 크기(magnitude)로 나눠준면 된다.
     2차원 벡터의 단위 벡터 = (x/magnitude, y/magnitude)
     
     * ※ std::hypot은 원점을 기준으로 입력된 지점까지의 거리를 구하는 함수이다.
     *  피타고라스 정리를 이용하여 두점 (0,0)과 (x,y)사이의
     *  유클리드 거리(Euclidean distance)를 구하는 방식이다.
     *  2차원 데카르프 좌표 평면상의 거리를 측정하는 방식 √(x^2 + y^2)을 사용하여 구함
    </pre>  */
    T Magnitude() const { return std::hypot(x, y); }

    /**<pre>
     * 어떤 벡터를 단위 벡터로 만드는 것을 정규화(Normalization)이라고 한다.
     * *단위 벡터(Unit Vector)란 방향을 가지는 크기가 1인 벡터를 말한다.
     * 단위 벡터(Unit Vector)는 벡터의 각 요소를 벡터의 크기(Magniture)로 나누면 구할 수 있다.
    </pre>  */
    Vector2D Normalize() const { return Vector2(x / Magnitude(), y / Magnitude()); }

    /**
     * x축의 양수 방향을 기준으로 이 벡터와 이루는 각도를 반환
     * @return  T   x축의 양수 방향을 기준으로 이 벡터와 이루는 각도를 반환
     */
    double AngleFromXAxis() const { return fmod(atan2(x, y) + 2 * PI, 2 * PI); }

    /**<pre>
     * 벡터 내적(스칼라 곱)을 의미한다.
     * 두 벡터 A,B의 각 구성 요소끼리의 곱의 합으로 표현할 수 있다.
      Dot = (A.x * B.x) + (A.y * B.y) 
     * 또는 두 벡터의 크기 곱하기 cosθ로 표현할 수도 있다.
      Dot = |A|*|B|*cosθ

     * 내적 결과 값의 부호에 따라 상대적인 방향성을 알 수 있다.
      Dot > 0 : 사이 각도가 90도 보다 작다
      Dot < 0 : 사이 각도가 90도 보다 크다
      Dot = 0 : 사이 각도가 90도(직각) 이다
      
     * 사이각이 0˚ or 180˚라면 cos0˚=1, cos180˚=-1
     * 사이각이 90˚에 가까워질수록 일치하는 방향 성분이 줄어들기 때문에 내적의 결과 값도 줄어든다.
     * 동일한 벡터를 내적한 결과 값은 벡터의 크기(magnitude)의 제곱이다.
     
     * 응용 분야
     - 어떤 물체가 바라보는 방향의 앞에 있는지 뒤에 있는지 판단 
     - 시야각 사이에 있는지 알 수 있음
     - 직각인지 확인
     - 각도 계산
     - 길이 계산(자신을 내적하고 제곱근을 구함)
     - 투영을 구하는데 사용

      </pre>*/
    T Dot(const Vector2D& other) const { return x * other.x + y * other.y; }

   /** <pre>
    * 두 벡터 A, B가 주어졌을 때, 벡터 v1과 v2의 외적 값을 반환
    * 외적 값 > 0: 벡터 B가 벡터 A의 반시계 방향(좌반원)에 있음.
    * 외적 값 < 0: 벡터 B가 벡터 A보다 시계 방향(우반원)에 있음.
    * 외적 값 = 0: 벡터 A와 B가 동일한 선상에 있음.

    * 2D벡터에서 외적은 두 벡터가 만드는 평행사변형의 면적을 나타낸다. 외적 값이 0이면 두 벡터가 평행.
    * 양수라면 other는 호출된 벡터의 반시계 방향에 있음. 음수라면 other는 호출된 벡터의 시계 방향에 있음 */
    T Cross(const Vector2D& other) const { return x * other.y - y * other.x; }

    /** 이 벡터를 other벡터에 사영한 결과를 반환 */
    Vector2D Project(const Vector2D& other) const
    {
        const Vector2D r = other.Normalize();
        return r * r.Dot(*this);
    }
};
