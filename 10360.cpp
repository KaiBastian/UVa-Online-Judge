#include <iostream>
#include <tuple>
#include <cstring>


unsigned grid_ [1025][1025];

class RatGrid
{
public:
	RatGrid(size_t bombReach) : bombReach_(bombReach)
	{
		std::memset(&grid_, 0, sizeof(grid_));
	}
	
	void addRatNest(size_t x, size_t y, size_t size)
	{
		const size_t startY = bombReach_ > y ? 0 : y - bombReach_;
		const size_t endY = bombReach_ + y > 1024 ? 1024 : bombReach_ + y;
		
		const size_t startX = bombReach_ > x ? 0 : x - bombReach_;
		const size_t endX = bombReach_ + x > 1024 ? 1024 : bombReach_ + x;
		
		for (size_t row = startX ; row <= endX ; ++row)
		{
			for (size_t column = startY; column <= endY ; ++column)
			{
				grid_[row][column] += size;
			}
		}
	}
	
	std::tuple<size_t, size_t, size_t> findBest()
	{
		size_t maxSoFar = 0;
		size_t x = 0;
		size_t y = 0;
		for (size_t row = 0 ; row <= 1024 ; ++row)
		{
			for (size_t column = 0; column <= 1024; ++column)
			{
				if (grid_[row][column] > maxSoFar)
				{
					maxSoFar = grid_[row][column];
					x = row;
					y = column;
				}
			}
		}
		return std::make_tuple(x, y, maxSoFar);
	}

private:
	size_t bombReach_;
};


int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	unsigned t;
	std::cin >> t;
	while (t-->0)
	{
		unsigned d, nests;
		std::cin >> d >> nests;
		
		RatGrid grid(d);
		while (nests-->0)
		{
			size_t x, y, size;
			std::cin >> x >> y >> size;
			grid.addRatNest(x, y, size);
		}
		
		auto result = grid.findBest();
		std::cout << std::get<0>(result) << ' ' << std::get<1>(result) << ' ' << std::get<2>(result) << '\n';	
	}
	
	
	return 0;
}
