#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const size_t length = std::sqrt(1000000000);

    size_t testCases;
    std::cin >> testCases;

    std::vector<size_t> solutions;
    for (size_t caseNum = 1; caseNum <= testCases; ++caseNum)
    {
        int n;
        std::cin >> n;
        for (size_t i = 1; i <= length; ++i)
        {
            int x = n - (int)i * i;
            if (x % i == 0 && x > 0)
                solutions.push_back(x);
        }
        std::sort(solutions.begin(), solutions.end());
        std::cout << "Case " << caseNum << ':';
        for (auto solution : solutions)
            std::cout << ' ' << solution;

        std::cout << '\n';
        solutions.clear();
    }
}
