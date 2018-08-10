#include <cstring>
#include <iostream>
#include <type_traits>

typedef std::integral_constant<unsigned, 200> maxMoney_;
typedef std::integral_constant<unsigned, 20> maxcatagory_;
typedef std::integral_constant<unsigned, 20> maxModels_;

bool reachable[maxcatagory_::value]
              [maxMoney_::value + 1]; // 0..19 * 0..200 // 0 money not used
unsigned priceList[maxcatagory_::value][maxModels_::value];
unsigned modelsPerCatagory[maxcatagory_::value];

class WeddingShopping
{
public:
    WeddingShopping(unsigned money, unsigned catagories)
        : money_(money), catagories_(catagories)
    {
        std::memset(&reachable, 0x0, sizeof(reachable));
    }

    bool bestFit(unsigned& money)
    {
        calculate();
        const unsigned lastCatagory = catagories_ - 1;
        for (unsigned i = money_; i >= 1; --i)
        {
            if (reachable[lastCatagory][i])
            {
                money = i;
                return true;
            }
        }
        return false;
    }

private:
    void calculate()
    {
        // fist catagory
        for (unsigned i = 0; i < modelsPerCatagory[0]; ++i)
        {
            const unsigned moneySpent = priceList[0][i];
            if (moneySpent > money_)
                continue;
            reachable[0][moneySpent] = true;
        }
        for (unsigned c = 1; c < catagories_; ++c)
        {
            // for all reachable in last c
            for (unsigned m = 1; m <= 200; ++m)
            {
                if (reachable[c - 1][m])
                {
                    // add all new choices
                    for (unsigned i = 0; i < modelsPerCatagory[c]; ++i)
                    {
                        const unsigned moneySpent = m + priceList[c][i];
                        if (moneySpent > money_)
                            continue;
                        reachable[c][moneySpent] = true;
                    }
                }
            }
        }
    }

private:
    unsigned money_;      // number of 1..200
    unsigned catagories_; // number of 1..20
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned t;
    std::cin >> t;
    while (t-- > 0)
    {
        unsigned m, c;
        std::cin >> m >> c;
        WeddingShopping wedding(m, c);
        for (unsigned currentC = 0; currentC < c; ++currentC)
        {
            unsigned models;
            std::cin >> models;
            modelsPerCatagory[currentC] = models;
            for (unsigned currentModel = 0; currentModel < models;
                 ++currentModel)
            {
                unsigned price;
                std::cin >> price;
                priceList[currentC][currentModel] = price;
            }
        }
        unsigned money;
        if (wedding.bestFit(money))
        {
            std::cout << money << '\n';
        }
        else
        {
            std::cout << "no solution\n";
        }
    }

    return 0;
}
