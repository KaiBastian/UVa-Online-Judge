#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int stations;
    vector<int> stationMap(1423);
    while (true)
    {
        cin >> stations;
        if (stations == 0)
            break;

        stationMap.resize(stations);
        for (int i = 0; i < stations; ++i)
            std::cin >> stationMap[i];

        bool possible = true;
        sort(stationMap.begin(), stationMap.end());
        for (int i = 0; i < stations - 1; ++i)
        {
            const int distanceToNext = stationMap[i + 1] - stationMap[i];
            if (distanceToNext > 200)
            {
                possible = false;
                break;
            }
        }
        // last to end of trip and back
        if ((1422 - stationMap[stations - 1]) > 100)
            possible = false;

        if (possible)
            cout << "POSSIBLE\n";
        else
            cout << "IMPOSSIBLE\n";
    }
}
