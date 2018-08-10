#include <iostream>
#include <vector>
# 11683

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    size_t height, width;
    while (true)
    {
        std::cin >> height >> width;
        if (height == 0 && width == 0)
            return 0;

        size_t laserDeactivationCount = 0;

        size_t oldHeight = height;
        size_t currentHeight;
        for (size_t column = 0; column < width; ++column)
        {
            std::cin >> currentHeight;
            if (currentHeight > oldHeight)
            {
                const size_t difference = currentHeight - oldHeight;
                laserDeactivationCount += difference;
            }
            oldHeight = currentHeight;
        }

        if (currentHeight < height) // last column special case
        {
            const size_t difference = height - currentHeight;
            laserDeactivationCount += difference;
        }

        std::cout << laserDeactivationCount << '\n';
    }
}
