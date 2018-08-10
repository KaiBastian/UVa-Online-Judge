#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

class UnionFind
{
public:
    UnionFind(size_t size) : nodes_(size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            nodes_[i] = i;
        }
    }
    size_t find(size_t node);
    void unite(size_t a, size_t b);

private:
    void update(size_t start, size_t group);
    size_t findWOUpdate(size_t node) const;

private:
    vector<size_t> nodes_;
};

size_t UnionFind::find(size_t node)
{
    size_t group = findWOUpdate(node);
    update(node, group);
    return group;
}

void UnionFind::unite(size_t a, size_t b)
{
    const size_t aGroup = findWOUpdate(a);
    const size_t bGroup = findWOUpdate(b);

    if (aGroup != bGroup)
    {
        nodes_[bGroup] = aGroup;
        update(a, aGroup);
        update(b, aGroup);
    }
}

void UnionFind::update(size_t start, size_t group)
{
    for (size_t currentNode = start, parent = nodes_[start];
         currentNode != parent; currentNode = parent, parent = nodes_[parent])
    {
        nodes_[currentNode] = group;
    }
}

size_t UnionFind::findWOUpdate(size_t node) const
{
    size_t currentNode = node;
    for (size_t parent = nodes_[node]; currentNode != parent;
         currentNode = parent, parent = nodes_[parent])
    {
    }
    return currentNode;
}

struct Edge
{
    unsigned from;
    unsigned to;
    size_t weight;
};

void sortEdges(std::vector<Edge>& edges)
{
    auto weightSorter = [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    };
    std::sort(edges.begin(), edges.end(), weightSorter);
}

void solve(std::vector<Edge>& edges, UnionFind& unions)
{
    size_t sumAll = 0;
    size_t sumMST = 0;
    for (Edge e : edges)
    {
        sumAll += e.weight;
        const auto groupFrom = unions.find(e.from);
        const auto groupTo = unions.find(e.to);
        if (groupFrom != groupTo)
        {
            unions.unite(e.from, e.to);
            sumMST += e.weight;
        }
    }

    std::cout << sumAll - sumMST << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned numVertices, numEdges;
    while (std::cin >> numVertices >> numEdges
           && ((numVertices != 0) & (numEdges != 0)))
    {
        UnionFind unions(numVertices);
        std::vector<Edge> edges;

        while (numEdges-- > 0)
        {
            Edge e;
            std::cin >> e.from >> e.to >> e.weight;
            edges.push_back(e);
        }

        sortEdges(edges);

        solve(edges, unions);
    }
}
