#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

class Knapsack01
{
public:
    struct Item
    {
        size_t weight;
        size_t value;
    };

    Knapsack01(size_t numItems) : items_() { items_.reserve(numItems); }

    void addItem(Item i) { items_.push_back(i); }

    Item at(size_t n) const { return items_.at(n); }

    struct TreasureState
    {
        size_t value;
        bitset<30> treasures; // the used ones
    };

    TreasureState bestSolution(size_t maxWeight)
    {
        const size_t weightEntries = maxWeight + 1;
        vector<TreasureState> rowA(weightEntries, {0, 0});
        vector<TreasureState> rowB(weightEntries, {0, 0});

        for (size_t i = items_[0].weight; i < weightEntries; ++i)
        {
            rowA[i] = {items_[0].value, 1};
        }

        TreasureState* pred = rowB.data();
        TreasureState* curr = rowA.data();

        for (size_t itemId = 1; itemId < items_.size(); ++itemId)
        {
            swap(pred, curr);
            for (size_t weight = 0; weight < weightEntries; ++weight)
            {
                curr[weight] = pred[weight];
                if (weight >= items_[itemId].weight)
                {
                    const size_t weightLeft = weight - items_[itemId].weight;
                    const size_t newValue =
                        pred[weightLeft].value + items_[itemId].value;
                    if (newValue > pred[weight].value)
                    {
                        bitset<30> newTreasures = pred[weightLeft].treasures;
                        newTreasures.set(itemId);
                        curr[weight] = {newValue, newTreasures};
                    }
                }
            }
        }

        return curr[maxWeight];
    }

private:
    vector<Item> items_;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t t, w;
    size_t numTreasures;
    bool isFirst = true;
    while (cin >> t >> w)
    {
        cin >> numTreasures;
        Knapsack01 knapsack(numTreasures);
        for (size_t i = 0; i < numTreasures; ++i)
        {
            size_t d, v;
            cin >> d >> v;
            knapsack.addItem({d, v});
        }

        // It's better to divide the time
        Knapsack01::TreasureState solution = knapsack.bestSolution(t / (3 * w));

        if (!isFirst) // weird formating requirement ...
        {
            cout << '\n';
        }
        isFirst = false;

        cout << solution.value << '\n';
        cout << solution.treasures.count() << '\n';
        for (size_t i = 0; i < 30; ++i)
        {
            if (solution.treasures.test(i))
            {
                Knapsack01::Item item = knapsack.at(i);
                cout << item.weight << ' ' << item.value << '\n';
            }
        }
    }

    return 0;
}
