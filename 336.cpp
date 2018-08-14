#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph
{
public:
    using NodeId = unsigned;
    using Distance = unsigned;

public:
    explicit Graph(unsigned n) : adjList_() { adjList_.reserve(n); }

    void addDirected(NodeId from, NodeId to) { adjList_[from].push_back(to); }

    void addUndirected(NodeId a, NodeId b)
    {
        addDirected(a, b);
        addDirected(b, a);
    }

    unordered_map<NodeId, Distance> BFS(NodeId start, unsigned cutoff) const
    {
        unordered_map<NodeId, Distance> distances;
        distances.reserve(adjList_.size());
        for (const auto& pair : adjList_)
        {
            distances[pair.first] = numeric_limits<Distance>::max();
        }

        // Not sure this can happen.
        if (adjList_.find(start) == adjList_.end())
            return distances;

        queue<NodeId> q;
        q.push(start);
        distances.at(start) = 0;

        while (!q.empty())
        {
            const Distance newDistance = distances.at(q.front()) + 1;
            if (newDistance > cutoff)
                break;
            const vector<NodeId>& neighbors = adjList_.at(q.front());
            for (const NodeId neighbor : neighbors)
            {
                const Distance oldDistance = distances[neighbor];
                if (newDistance < oldDistance)
                {
                    distances[neighbor] = newDistance;
                    q.push(neighbor);
                }
            }

            q.pop();
        }

        return distances;
    }

private:
    unordered_map<NodeId, vector<NodeId>> adjList_;
};

void solve(unsigned NC, unsigned& testcaseNumber)
{
    Graph g(30);
    for (unsigned i = 0; i < NC; ++i)
    {
        unsigned a, b;
        cin >> a >> b;
        g.addUndirected(a, b);
    }

    unsigned start, TTL;
    while (cin >> start >> TTL && (start != 0 || TTL != 0))
    {
        unordered_map<Graph::NodeId, Graph::Distance> BFSResult =
            g.BFS(start, TTL);
        auto distanceIsMax = [](pair<const Graph::NodeId, Graph::Distance>& p) {
            return p.second == numeric_limits<Graph::Distance>::max();
        };
        auto unreachedNodes =
            count_if(BFSResult.begin(), BFSResult.end(), distanceIsMax);

        cout << "Case " << testcaseNumber << ": " << unreachedNodes
             << " nodes not reachable from node " << start
             << " with TTL = " << TTL << ".\n";
        testcaseNumber++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned NC;
    unsigned testcaseNumber = 1u;
    while (cin >> NC && NC != 0u)
    {
        solve(NC, testcaseNumber);
    }

    return 0;
}
