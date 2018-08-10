#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <utility>

std::array<size_t, 21> faculties;

void facInit()
{
    faculties[0] = std::numeric_limits<size_t>::max();
    faculties[1] = 1;
    for (size_t i = 2; i <= 20; ++i)
    {
        faculties[i] = faculties[i - 1] * i;
    }
}

// always sorted, constant lookup, constant removeal of ith element while
// staying sorted
struct MagicString
{
    MagicString(std::string&& orgString) : string(orgString)
    {
        std::sort(string.begin(), string.end());
    }

    char operator[](size_t index) // also removes the element if not last
    {
        const char retVal = string[index];

        const bool isLast = (string.size() - 1) == index;
        std::swap(string[index], string[string.size() - 1]);
        string.pop_back();
        if (!isLast)
            std::sort(string.begin() + index, string.end());

        return retVal;
    }

    std::string string;
};

void solve(MagicString& string, size_t k)
{
    while (!string.string.empty())
    {
        const size_t currentLength = string.string.size();
        const size_t currentFaculty = faculties[currentLength - 1];
        const size_t index = k / currentFaculty;
        k = k % currentFaculty;
        const char currentChar = string[index];
        std::cout << currentChar;
    }
    std::cout << '\n';
}

void solveSingleCase()
{
    std::string string;
    std::getline(std::cin, string);

    size_t k;
    std::cin >> k;
    std::string waste;
    std::getline(std::cin, waste);

    std::sort(string.begin(), string.end());

    MagicString magic(std::move(string));
    solve(magic, k);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    facInit();

    unsigned samples;
    std::cin >> samples;
    std::string waste;
    std::getline(std::cin, waste);
    while (samples-- > 0)
    {
        solveSingleCase();
    }
}
