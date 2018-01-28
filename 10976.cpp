#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	size_t k;
	vector<size_t> solutions;
	while (cin >> k)
	{
		for (size_t i = k + 1; i <= 2 * k; ++i)
		{
			if ((k * i) % (i - k) == 0)
				solutions.push_back(i);
		}

		cout << solutions.size() << '\n';
		for (const size_t x : solutions)
		{
			const size_t y = (k * x) / (x - k);
			cout << "1/" << k << " = 1/" << y << " + 1/" << x << '\n';
		}
		solutions.clear();
	}

	return 0;
}
