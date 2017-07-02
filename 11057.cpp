#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// This is a linear time solution instead of the obvious O(n*log(n))
//solution. (If sorting happens in O(n).)
int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t numBooks;
    while (cin >> numBooks)
    {
        vector<size_t> books;
        books.reserve(numBooks);

        for (size_t i = 0; i < numBooks; ++i)
        {
            size_t price;
            cin >> price;
            books.push_back(price);
        }

        size_t target;
        cin >> target;

        sort(books.begin(), books.end());

        size_t lower = 0;
        size_t upper = books.size() - 1;
        size_t bestLower;
        size_t bestUpper;

        while (lower < upper)
        {
            const size_t currPrice = books[lower] + books[upper];
            if (currPrice == target)
            {
                bestLower = lower;
                bestUpper = upper;
                ++lower;
                --upper;
            }
            else if (currPrice < target)
                ++lower;
            else
                --upper;
        }

        cout << "Peter should buy books whose prices are "
             << books[bestLower] << " and " << books[bestUpper] << ".\n\n";
    }

return 0;
}
