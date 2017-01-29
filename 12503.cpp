#include <iostream>
#include <vector>
//12503

void advanceCINbyChars(unsigned n)
{
	char trash;
	for (unsigned i = 0; i < n; ++i)
		std::cin >> trash;
}
int getAction(const std::vector<int>& executedInstructions)
{
	char firstLetter;
	std::cin >> firstLetter;
	if (firstLetter == 'R')
	{
		advanceCINbyChars(4);
		return 1;
	}
	if (firstLetter == 'L')
	{
		advanceCINbyChars(3);
		return -1;
	}
	
	advanceCINbyChars(5);
	
	unsigned referencedInstruction;
	std::cin >> referencedInstruction;
	int action = executedInstructions[referencedInstruction - 1];
	return action;
}

void solveCase()
{
	unsigned numberOfInstructions;
	std::cin >> numberOfInstructions;
	
	std::vector<int> executedInstructions(numberOfInstructions);
	int currentPosition = 0;
	for (unsigned i = 0; i < numberOfInstructions; ++i)
	{
		int action = getAction(executedInstructions);
		executedInstructions[i] = action;
		currentPosition += action;	
	}
	std::cout << currentPosition << '\n';
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int numberOfTestcases;
	std::cin >> numberOfTestcases;
	while (numberOfTestcases-- > 0)
	{
		solveCase();
	}
}
