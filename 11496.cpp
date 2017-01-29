#include<iostream>

using namespace std;

int main()
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	
	int samples;
	while (true)
	{
		cin >> samples;
		if (samples == 0)
			break;
		
		/*const*/int h1;
		cin >> h1;
		
		/*const*/int h2;
		cin >> h2;
		
		// below logic needs three samples
		if (samples == 2)
		{
			std::cout << "2\n";
			continue;
		}
		
		int numberOfPeaks  = 0;
		bool down = h1 > h2; //the incomming edge to HiMinus1 down or up
		int hiMinus1 = h2;	
		
		// we start by deciding whether H2 is a peak
		for (int i = 3; i <= samples; ++i)
		{
			int hi;
			cin >> hi;
			if (down)
			{
				if (hiMinus1 < hi) // but next is up
				{
					down = false;
					++numberOfPeaks;
				}
			}
			else // up
			{
				if (hiMinus1 > hi) // but next is down
				{
					down = true;
					++numberOfPeaks;
				}
			}
			hiMinus1 = hi;					
		}
		
		// We still need to take care of HN and H1
		const int HN = hiMinus1;
		// down is the edge from HNMinus1 to HN
		if (down)
		{
			if (HN < h1)
			{
				down = false;
				++numberOfPeaks;
			}
		}
		else // up
		{
			if (HN > h1)
			{
				down = true;
				++numberOfPeaks;
			}
		}
		
		// h1
		if (down)
		{
			if (h1 < h2)
				++numberOfPeaks;
		}
		else // up
		{
			if (h1 > h2)
				++numberOfPeaks;
		}
		
		cout << numberOfPeaks << '\n';		
	}
	
}
