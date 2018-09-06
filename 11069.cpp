#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<size_t> solutions = {1, 2, 2, 3, 4};
    for (size_t i = 5; i < 76; ++i)
    {
        solutions.push_back(solutions[i - 2] + solutions[i - 3]);
    }
    
    size_t question;
    while (cin >> question)
    {
        cout << solutions[question - 1] << '\n';
    }
};
