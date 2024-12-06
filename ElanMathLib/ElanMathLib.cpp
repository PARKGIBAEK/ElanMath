#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;

    /** 점들을 정렬할 때 y값이 작은 순서대로 정렬한다. y값이 같다면 x값이 작은 순서대로 정렬한다.<br/>
     * 최종적으로 0번째 원소는 y값이 가장 작은 원소들 중 x값이 가장 작은 원소가 오게 된다  
     * (Monotone's Scan을 수행하기 위한 사전 정렬에 필요한 비교자).
     */
    bool operator<(const Point& p) const
    {
        return x == p.x ? y < p.y : x < p.x;
    }
};

/**
 *<pre>
 * 벡터 OA와 OB를 외적한 결과 값을 반환한다.
 * 
 * 활용 방식 1.
 * 벡터 OA와 벡터 OB를 외적한 결과값의 부호에 따라
 * 점 B가 벡터 OA를 기준으로 반시계방향(좌반원)인지 시계방향(우반원)인지 알아낼 수 있다
    
 * 근거 :
 * 외적은 두 벡터OA와 OB가 이루는 평면의 면적과도 같다.
 * 따라서 OA와 OB를 곱한 면적이 양수가 되면 
 * 벡터 OA = (OA.x, OA.y) = (A.x-O.x, A.y-O.y)
 * 벡터 OB = (OB.x, OB.y) = (B.x-O.x, B.y-O.y)
 * cross(OA, OB) = (OA.x*OB.y)-(OB.x*OA.y) = (A.x-O.x)*(B.y-O.y) - (A.y-O.y)*(B.x-O.x)
 * 
 *      cross(OA, OB) > 0 : 점 c가 점 a를 기준으로 점 b의 반시계 방향에 있음
 *      
               B
              /
             /
            O ----> A

 *      cross(OA, OB) < 0 : 점 c가 점 a를 기준으로 점 b의 시계 방향에 있음
 *      
            O ----> A
             \
              \
               B

 *      cross(OA, OB) = 0 : 점 a,b,c가 일직선상에 있음
 *      
            O ----> A ----> B
 </pre>
 */
int cross(const Point& O, const Point& A, const Point& B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

/** Monotone Chain 방식으로 Convex Hull을 완성한다
 * Convex Hull의 하부를 먼저 구하고 상부를 구함.
 */
vector<Point> FindConvexHullWithMonotoneChain(vector<Point>& points)
{
    if (points.size() <= 1) return points;

    sort(points.begin(), points.end()); // Step 1: 정렬

    vector<Point> hull;

    // Lower hull
    for (const auto& p : points)
    {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), p) <= 0)
        {
            hull.pop_back();
        }
        hull.emplace_back(p);
    }

    // Upper hull
    const size_t lower_size = hull.size();
    for (auto it = points.rbegin(); it != points.rend(); ++it)
    {
        while (hull.size() > lower_size && cross(hull[hull.size() - 2], hull.back(), *it) <= 0)
        {
            hull.pop_back();
        }
        hull.emplace_back(*it);
    }

    hull.pop_back(); // 마지막 점이 중복되므로 제거
    return hull;
}

int main()
{
    vector<Point> points = {{4, 2}, {2, 0}, {1, 1}, {2, 4}, {4, 3}, {2, 2}, {0, 0}, {3, 3}, {2, 2}, {1, 3}};
    vector<Point> result = FindConvexHullWithMonotoneChain(points);

    cout << "Convex Hull Points:\n";
    for (const auto& p : result)
    {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
    return 0;
}



void find_start_point(vector<Point>& points)
{
    int min_idx = 0;
    for (int i = 1; i < points.size(); i++)
    {
        if (points[min_idx].y > points[i].y ||
            (points[min_idx].y == points[i].y && points[min_idx].x > points[i].x))
        {
            min_idx = i;
        }
    }
    swap(points[min_idx], points[0]);
}

void sort_to_graham_scan(vector<Point>& points)
{
    
}