#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <unordered_set>
#include <queue>

using namespace std;

class Graph
{
public:
    using NodeId = size_t;
    using Weight = size_t;
    
    struct Neighbor
    {
        NodeId id;
        Weight cost;
    };

    Graph(size_t numNodes, size_t numHotels)
        : adjList_(), hotels_()
    {
        adjList_.reserve(numNodes);
        hotels_.reserve(numHotels);
    }

    void addUndirected(NodeId a, NodeId b, Weight w)
    {
        if (a == b)
            return;
        adjList_[a].push_back({b, w});
        adjList_[b].push_back({a, w});
    }

    void addHotel(NodeId id)
    {
        hotels_.insert(id);
    }

    int hotelDijkstra(NodeId start, NodeId end)
    {
        // We don't account for nodes that don't have edges going out.
        // But this could as well be the start node.
        if (adjList_.find(start) == adjList_.end())
        {
            return -1;
        }

        hotels_.insert(start); // start and end might as well be a hotel
        hotels_.insert(end);
        
        // hotels and start and end are new nodes.
        // We want BFS through those nodes in a lazy fashion.
        unordered_map<NodeId, unordered_set<NodeId>> newAdjList;
        struct State
        {
            NodeId id;
            size_t numSteps;
        };
        
        queue<State> q;
        q.push({start, 0});

        while (!q.empty())
        {
            State curr = q.front();
            if (newAdjList.find(curr.id) == newAdjList.end())
            {
                newAdjList.insert(make_pair(
                    curr.id, getReachableNodes(curr.id)));
                for (NodeId neighbor : newAdjList.at(curr.id))
                {
                    if (neighbor == end)
                        return curr.numSteps;
                    q.push({neighbor, curr.numSteps + 1});
                }
            }
            q.pop();
        }
        return -1;   
    }

private:
    unordered_set<NodeId> getReachableNodes(NodeId start) const
    {
        unordered_map<NodeId, size_t> distances;
        for (const auto& nodePair : adjList_)
        {
            distances[nodePair.first] = numeric_limits<size_t>::max();
        }
        distances[start] = 0;

        struct State
        {
            NodeId id;
            size_t cost;
            bool operator<(State other) const
            {
                return cost > other.cost;
            }
        };

        priority_queue<State> q;
        q.push({start, 0});

        unordered_set<NodeId> ret;
        while (!q.empty())
        {
            State curr = q.top();
            // We cannot use decreas key
            if (curr.cost > distances.at(curr.id))
            {
                q.pop();
                continue;
            }

            if (hotels_.find(curr.id) != hotels_.end())
                ret.insert(curr.id);
            
            for (Neighbor n : adjList_.at(curr.id))
            {
                const size_t oldDistance = distances.at(n.id);
                const size_t newDistance =
                    distances.at(curr.id) + n.cost;
                if (newDistance <= 600 && oldDistance > newDistance)
                {
                    distances.at(n.id) = newDistance;
                    q.push({n.id, newDistance});
                }                
            }

            q.pop();
        }
        return ret;       
    }

private:
    unordered_map<NodeId, vector<Neighbor>> adjList_;
    unordered_set<NodeId> hotels_;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t numCities;
    while (cin >> numCities && numCities != 0)
    {
        size_t numHotels;
        cin >> numHotels;
        Graph g(numCities, numHotels);
        for (size_t i = 0; i < numHotels; ++i)
        {
            size_t hotelCity;
            cin >> hotelCity;
            g.addHotel(hotelCity);
        }
        size_t numEdges;
        cin >> numEdges;
        for (size_t i = 0; i < numEdges; ++i)
        {
            size_t from, to, weight;
            cin >> from >> to >> weight;
            g.addUndirected(from, to, weight);
        }

        const int solution = g.hotelDijkstra(1, numCities);
        cout << solution << '\n';
    }
}
