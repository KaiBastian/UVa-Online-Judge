#include <cstring>
#include <iostream>

unsigned ageCount[101]; // 0..100

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::memset(ageCount, 0, sizeof(ageCount));

    while (true)
    {
        unsigned numbers;
        std::cin >> numbers;
        if (numbers == 0)
            break;

        while (numbers-- > 0)
        {
            unsigned age;
            std::cin >> age;
            ageCount[age]++;
        }

        unsigned firstAge = 1;
        for (; firstAge <= 100; ++firstAge)
        {
            if (ageCount[firstAge] == 0)
            {
                continue;
            }
            else
            {
                ageCount[firstAge]--;
                std::cout << firstAge;
                break;
            }
        }

        for (unsigned age = firstAge; age <= 100; ++age)
        {
            while (ageCount[age] > 0)
            {
                ageCount[age]--;
                std::cout << ' ' << age;
            }
        }
        std::cout << '\n';
    }
}
