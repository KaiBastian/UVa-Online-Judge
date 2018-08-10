#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph
{
public:
    Graph(size_t nodeCount) : adjList_(nodeCount) {}

    void addDirectedEdge(size_t from, size_t to, size_t weight)
    {
        adjList_[from].push_back(Edge(to, weight));
    }

    class BellmanFordState
    {
    public:
        BellmanFordState(size_t nodeCount)
            : distance_(nodeCount, numeric_limits<size_t>::max())
        {
            distance_[0] = 0;
        }

        size_t getLastDistance() const { return distance_.back(); }

    private:
        vector<size_t> distance_;

        friend class Graph;
    };

    BellmanFordState bellmanFordStep(const BellmanFordState& oldState)
    {
        BellmanFordState newState(oldState);
        for (size_t source = 0; source < adjList_.size(); ++source)
        {
            if (oldState.distance_[source] == numeric_limits<size_t>::max())
                continue;
            for (const Edge e : adjList_[source])
            {
                const size_t newCost = oldState.distance_[source] + e.weight;
                if (newState.distance_[e.target] > newCost)
                {
                    newState.distance_[e.target] = newCost;
                }
            }
        }
        return newState;
    }

private:
    struct Edge
    {
        Edge(size_t target, size_t weight) : target(target), weight(weight) {}

        size_t target;
        size_t weight;
    };
    vector<vector<Edge>> adjList_;
};

void setupCityMap(unordered_map<string, size_t>& cityMap)
{
    // We expect Calgary to be the first city and Fredericton to be the
    // last. Otherwiese the Graph gets into trouble.
    size_t numCities;
    cin >> numCities;

    cityMap.reserve(numCities);

    for (size_t cityNumber = 0; cityNumber < numCities; ++cityNumber)
    {
        string s;
        cin >> s;
        cityMap.insert(make_pair(s, cityNumber));
    }
}

void setupEdges(Graph& g, const unordered_map<string, size_t>& cityMap)
{
    size_t numEdges;
    cin >> numEdges;
    for (size_t edgeNum = 0; edgeNum < numEdges; ++edgeNum)
    {
        string from, to;
        size_t weight;
        cin >> from >> to >> weight;
        g.addDirectedEdge(
            cityMap.find(from)->second, cityMap.find(to)->second, weight);
    }
}

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t scenarios;
    cin >> scenarios;

    for (size_t scenario = 1; scenario <= scenarios; ++scenario)
    {
        if (scenario != 1)
            cout << '\n';

        unordered_map<string, size_t> cityMap;
        setupCityMap(cityMap);

        Graph g(cityMap.size());
        setupEdges(g, cityMap);

        size_t numQueries;
        cin >> numQueries;
        vector<size_t> queries(numQueries);
        for (size_t& q : queries)
        {
            cin >> q;
        }
        const size_t numSteps =
            *max_element(queries.begin(), queries.end()) + 1;

        vector<size_t> answers(numSteps);
        Graph::BellmanFordState state(cityMap.size());
        for (size_t& answer : answers)
        {
            state = g.bellmanFordStep(state);
            answer = state.getLastDistance();
        }

        cout << "Scenario #" << scenario << '\n';
        for (const size_t q : queries)
        {
            if (answers[q] == numeric_limits<size_t>::max())
                cout << "No satisfactory flights\n";
            else
                cout << "Total cost of flight(s) is $" << answers[q] << '\n';
        }
    }

    return 0;
}
