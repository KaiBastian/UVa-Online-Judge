#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdint>

using namespace std;
struct point
{
    point (int64_t x, int64_t y)
    : x(x), y(y)
    {}

    bool operator < (const point& other) const
    {
        if ( x != other.x)
            return x < other.x;
        return y < other.y;
    }

    int64_t x;
    int64_t y;
};

// returns true, iff c lies to the right of the oriented edge (a,b)
inline bool rightOf(const point& a, const point& b, const point& c)
{
    // This logic is derived from the three dimensional cross product.
    // Basically your thump is (a,b), your index finger is (b,c), so
    // your middle finger should point downwards.
    const int64_t z = (b.x - a.x) * (c.y - a.y)
                      - (c.x - a.x) * (b.y - a.y);
    return z < 0;
}

void parseInput(vector<point>& input)
{
    unsigned numberOfPoints;
    cin >> numberOfPoints;

    for (unsigned i = 0; i < numberOfPoints; ++i)
    {
        int x, y;
        char isOn;
        cin >> x  >> y >> isOn;
        if (isOn == 'Y')
            input.push_back(point(x,y));
    }
}

void print(const vector<point>& convexHullPoints)
{
    cout << convexHullPoints.size() - 1u << '\n';
    for (auto it = convexHullPoints.begin();
         it != prev(convexHullPoints.end());
         ++it)
    {
        cout << it->x << ' ' << it->y << '\n';
    }
}

void tryNewPoint(vector<point>& convexHullPoints, const point& p,
                 size_t threshold)
{
    while (convexHullPoints.size() >= threshold)
    {
        const auto last = prev(convexHullPoints.end());
        const auto secondLast = prev(last);
        if (rightOf(*secondLast, *last, p))
            convexHullPoints.pop_back();
        else
            break;
    }
    convexHullPoints.push_back(p);
}

void solveTestcase()
{
    vector<point> input;
    parseInput(input);
    sort(input.begin(), input.end());

    vector<point> convexHullPoints;
    for (const auto& p : input)
    {
        tryNewPoint(convexHullPoints, p, 2u);
    }

    // visiting (almost) all points in reverse to build upper.
    // last point (n-1) is already in.
    // The threshold hits in after we inserted the first point.
    // That point may be wrong already.
    const size_t threshold = convexHullPoints.size() + 1;
    for (int i = input.size() - 2; i >=0; --i)
    {
        tryNewPoint(convexHullPoints, input[i], threshold);
    }

    print(convexHullPoints);
}

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    unsigned testcases;
    cin >> testcases;
    for (unsigned i = 0; i < testcases; ++i)
    {
        solveTestcase();
    }
}
