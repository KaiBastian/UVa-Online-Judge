#include <iostream>
#include <vector>

using namespace std;

int main()
{
	std::cin.tie(nullptr);
	std::ios::sync_with_stdio(false);
	
	int numberOfCars;
	while (true)
	{
		std::cin >> numberOfCars;
		if (numberOfCars == 0)
			return 0;
		
		vector<int> startingFormation(numberOfCars + 1, 0); // pos 0 not used, 0 for unknown car number
		int currentPos = 1;
		bool possible = true;
		for (; currentPos <= numberOfCars; ++currentPos)
		{
			int carNumber;
			int change;
			std::cin >> carNumber >> change;
			const int startPos = currentPos + change;
			if (startPos <= 0 || startPos > numberOfCars)
			{
				possible = false;
				++currentPos;
				break;
			}
			if (startingFormation[startPos] != 0)
			{
				possible = false;
				++currentPos;
				break;
			}
			startingFormation[startPos] = carNumber;
		}
		for (; currentPos <= numberOfCars; ++currentPos)
		{
			int carNumber, change;
			std::cin >> carNumber >> change;
		}
		if (!possible)
		{
			std::cout << "-1\n";
		}
		else
		{
			std::cout << startingFormation[1];
			for (int pos = 2; pos <= numberOfCars; ++pos)
			{
				std::cout << ' ' << startingFormation[pos];
			}
			std::cout << '\n';
		}		
	}	
}
