#include <iostream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

template <typename sequence_order>
class optimal_sequence
{
    using sequence_type = map<unsigned, unsigned, sequence_order>;
    using iterator = typename sequence_type::iterator;
    using key_type = typename sequence_type::key_type;

public:
    void insert(key_type height, unsigned width)
    {
        // This insert functions does at worst 2 lookups of the element
        // in the map. This could be reduces, but I liked the logic
        // better the way it is.
        if (sequence_endings.empty())
        {
            sequence_endings.insert(make_pair(height, width));
            return;
        }

        auto find_result = sequence_endings.find(height);
        if (find_result != sequence_endings.end())
        {
            // Element is already in there.
            // Here we just need to see whether the current building is
            //  wider.
            const unsigned pre_sequence_length =
                prev_element_acc_width(find_result);
            const unsigned this_buildings_acc_width =
                pre_sequence_length + width;
            if (this_buildings_acc_width <= find_result->second)
                return; // It's not.
            // It is.
            // We need to update and maintain the monotone property.
            find_result->second = this_buildings_acc_width;
            restore_property(find_result);
            return;
        }

        auto prev_e = prev_element(height);
        if (prev_e == sequence_endings.end())
        {
            sequence_endings.insert(
                sequence_endings.begin(), make_pair(height, width));
            restore_property(sequence_endings.begin());
            return;
        }

        const typename sequence_type::key_type newWidth =
            prev_e->second + width;
        sequence_endings.insert(
            next(prev_e), make_pair(height, newWidth));
        restore_property(next(prev_e));
    }

    unsigned best_width() const
    {
        return sequence_endings.rbegin()->second;
    }

private:
    // This assumes we alread know that there is no element with key
    // 'height' in the sequence and we know the sequence is not empty.
    iterator prev_element(typename sequence_type::key_type height)
    {
        auto lower_bound = sequence_endings.lower_bound(height);
        if (lower_bound == sequence_endings.begin())
            return sequence_endings.end();
        return prev(lower_bound);
    }

    unsigned prev_element_acc_width(iterator& it)
    {
        if (it == sequence_endings.begin())
            return 0u;
        else
            return prev(it)->second;
    }

    void restore_property(iterator it)
    {
        // When we find the first element that is compliant,
        // we can stop, because we know the property is not violated
        // after that element.
        const unsigned width = it->second;
        ++it;
        while (it != sequence_endings.end())
        {
            if (it->second >= width)
                break;

            sequence_endings.erase(it++);
        }
    }

private:
    // key is the current height, value is the accumulated width i
    // ncluding all buildings in the sequence.
    // Say two elements have key' and key'' and key' < key'', then
    // value' < value''.
    // That is to say all elements in this container are optimal
    // sequence endings with respect to their individual height.
    map<unsigned, unsigned, sequence_order> sequence_endings;
};

void solveCase(unsigned caseNumber)
{
    unsigned numberOfBuildings;
    cin >> numberOfBuildings;

    vector<unsigned> heights, widths;
    heights.reserve(numberOfBuildings);
    widths.reserve(numberOfBuildings);
    for (unsigned i = 0; i < numberOfBuildings; ++i)
    {
        unsigned height;
        cin >> height;
        heights.push_back(height);
    }
    for (unsigned i = 0; i < numberOfBuildings; ++i)
    {
        unsigned width;
        cin >> width;
        widths.push_back(width);
    }

    optimal_sequence<std::greater<unsigned>> decreasing_sequence;
    optimal_sequence<std::less<unsigned>> increasing_sequence;

    for (unsigned i = 0; i < heights.size(); ++i)
    {
        decreasing_sequence.insert(heights[i], widths[i]);
        increasing_sequence.insert(heights[i], widths[i]);
    }

    cout << "Case " << caseNumber << ". ";
    if (decreasing_sequence.best_width() <=
        increasing_sequence.best_width())
    {
        cout << "Increasing (" << increasing_sequence.best_width()
        << "). Decreasing (" << decreasing_sequence.best_width()
        << ").";
    }
    else
    {
        cout << "Decreasing (" << decreasing_sequence.best_width()
        << "). Increasing (" << increasing_sequence.best_width()
        << ").";
    }
    cout << '\n';
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    unsigned t;
    cin >> t;
    for (unsigned i = 1; i <= t; ++i)
    {
        solveCase(i);
    }
}
