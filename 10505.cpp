#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
// 10505

/*
 * The input data is not correct according to the specification.
 * The input data can not be assumed to specify a bipartite graph,
 * nor can it be assumed to have edges with endpoints < N.
 * The expected behavior on non-bipartite graphs is that the
 * non-bipartite component is completely ignored.
 */

using namespace std;

class Graph
{
public:
    Graph(unsigned numberOfNodes) : adjList_(numberOfNodes) {}

    void addUndirectedEdge(unsigned a, unsigned b)
    {
        // Input data is messed up...
        if (a >= adjList_.size() || b >= adjList_.size())
            return;

        adjList_[a].push_back(b);
        adjList_[b].push_back(a);
    }

    unsigned largestBiPartition() const
    {
        vector<color> coloring(adjList_.size(), color::unknown);
        unsigned largestBiPartition = 0;

        // for every node
        for (unsigned i = 0; i < adjList_.size(); ++i)
        {
            if (coloring[i] == color::unknown)
            {
                unsigned thisConnection;
                try
                {
                    thisConnection = findLargestBiPartition(coloring, i);
                }
                catch (Graph::NotBipartite& e)
                {
                    thisConnection = 0;
                }
                largestBiPartition += thisConnection;
            }
        }

        return largestBiPartition;
    }

private:
    class NotBipartite
    {
    };

    enum class color
    {
        black = 0,
        white = 1,
        unknown
    };

    // for all nodes that are connected to node i
    unsigned findLargestBiPartition(vector<color>& coloring, unsigned i) const
    {
        unsigned colorCounts[] = {0, 0};
        bool isBipartiton = true;
        stack<unsigned> s;
        s.push(i);
        coloring[i] = color::black;
        ++colorCounts[static_cast<unsigned>(color::black)];

        while (!s.empty())
        {
            const unsigned currentNode = s.top();
            s.pop();
            const color currentColor = coloring[currentNode];
            const color nextColor =
                currentColor == color::black ? color::white : color::black;

            for (unsigned neighbor : adjList_[currentNode])
            {
                if (coloring[neighbor] == color::unknown)
                {
                    s.push(neighbor);
                    coloring[neighbor] = nextColor;
                    ++colorCounts[static_cast<unsigned>(nextColor)];
                }
                else if (coloring[neighbor] == currentColor)
                    isBipartiton = false;
            }
        }

        if (!isBipartiton)
            throw NotBipartite();

        return max(colorCounts[0], colorCounts[1]);
    }

private:
    vector<vector<unsigned>> adjList_;
};

void solveSingleCase()
{
    unsigned numberOfPeople;
    cin >> numberOfPeople;
    Graph g(numberOfPeople);

    for (unsigned i = 0; i < numberOfPeople; ++i)
    {
        unsigned numberOfEnemies;
        cin >> numberOfEnemies;
        for (unsigned j = 0; j < numberOfEnemies; ++j)
        {
            unsigned enemy;
            cin >> enemy;
            const unsigned graphNodeEnemy = enemy - 1;
            g.addUndirectedEdge(i, graphNodeEnemy);
        }
    }

    const unsigned solution = g.largestBiPartition();
    cout << solution << '\n';
}

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    unsigned testcases;
    cin >> testcases;
    for (decltype(testcases) i = 0; i < testcases; ++i)
    {
        solveSingleCase();
    }
}
