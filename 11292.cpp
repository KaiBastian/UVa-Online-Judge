#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool solve(
    vector<unsigned>& headDiameters,
    vector<unsigned>& knightHeights,
    unsigned& solution)
{
    if (headDiameters.size() > knightHeights.size())
        return false;

    sort(headDiameters.begin(), headDiameters.end());
    sort(knightHeights.begin(), knightHeights.end());

    unsigned cost = 0;
    unsigned cheapestKnightPos = 0;
    for (unsigned headDiameter : headDiameters)
    {
        while (cheapestKnightPos < knightHeights.size()
               && headDiameter > knightHeights[cheapestKnightPos])
        {
            ++cheapestKnightPos;
        }
        if (cheapestKnightPos == knightHeights.size())
            return false;
        cost += knightHeights[cheapestKnightPos];
        ++cheapestKnightPos;
    }

    solution = cost;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<unsigned> headDiameters;
    vector<unsigned> knightHeights;

    headDiameters.reserve(20000);
    knightHeights.reserve(20000);
    while (true)
    {
        unsigned numHeads, numKnights;
        cin >> numHeads >> numKnights;
        if (numHeads == 0 && numKnights == 0)
            break;

        headDiameters.clear();
        for (unsigned i = 0; i < numHeads; ++i)
        {
            unsigned d;
            cin >> d;
            headDiameters.push_back(d);
        }
        knightHeights.clear();
        for (unsigned i = 0; i < numKnights; ++i)
        {
            unsigned h;
            cin >> h;
            knightHeights.push_back(h);
        }

        unsigned solution;
        const bool possible = solve(headDiameters, knightHeights, solution);
        if (!possible)
            cout << "Loowater is doomed!";
        else
            cout << solution;
        cout << '\n';
    }

    return 0;
}
