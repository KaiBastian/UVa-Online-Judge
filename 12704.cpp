#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);
    size_t numT;
    cin >> numT;
    for (size_t i = 0; i < numT; ++i)
    {
        double x,y,r;
        cin >> x >> y >> r;
        const double distanceFromCenter = hypot(x,y);
        const double shortest = r - distanceFromCenter;
        const double longest = r + distanceFromCenter;
        cout << shortest << ' ' << longest << '\n';
    }
}
