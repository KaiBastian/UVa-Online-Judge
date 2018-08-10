#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph
{
public:
    void addEdge(unsigned from, unsigned to)
    {
        adjList.insert(std::make_pair(from, std::vector<unsigned>()));
        adjList.insert(std::make_pair(to, std::vector<unsigned>()));
        adjList.find(from)->second.push_back(to);
    }

    bool isTree()
    {
        if (adjList.empty()) // Empty graph is a connected and cycle free.
            return true;

        auto getRootResult = getRoot();
        if (!getRootResult.second) // Not exactly one root.
            return false;

        const unsigned root = getRootResult.first;

        std::unordered_set<unsigned> visitedNodes;
        std::stack<unsigned> nodesToVisit;
        nodesToVisit.push(root);

        while (!nodesToVisit.empty())
        {
            const unsigned currentNode = nodesToVisit.top();
            nodesToVisit.pop();
            auto visitationResult = visitedNodes.insert(currentNode);
            if (!visitationResult.second) // Cycle.
                return false;

            auto findResult = adjList.find(currentNode);
            for (const auto child : findResult->second)
                nodesToVisit.push(child);
        }

        return visitedNodes.size() == adjList.size(); // Not connected.
    }

private:
    std::pair<unsigned, bool> getRoot()
    {
        std::unordered_set<unsigned> rootCandidates;
        for (const auto& node : adjList)
        {
            rootCandidates.insert(node.first);
        }

        for (const auto& node : adjList)
        {
            for (unsigned target : node.second)
            {
                auto findResult = rootCandidates.find(target);
                if (findResult != rootCandidates.end())
                    rootCandidates.erase(findResult);
            }
        }

        if (rootCandidates.size() == 1)
        {
            const unsigned root = *rootCandidates.begin();
            return std::make_pair(root, true);
        }
        return std::make_pair(0, false);
    }

private:
    std::unordered_map<unsigned, std::vector<unsigned>> adjList;
};

bool solveCase(size_t caseNumber)
{
    Graph g;
    while (true)
    {
        int from, to;
        std::cin >> from >> to;
        if (from < 0 && to < 0)
            return false;
        if (from == 0 && to == 0)
            break;

        g.addEdge(from, to);
    }

    std::cout << "Case " << caseNumber << " is ";
    if (!g.isTree())
        std::cout << "not ";

    std::cout << "a tree.\n";
    return true;
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    for (size_t caseNumber = 1; solveCase(caseNumber); ++caseNumber)
    {
    }
}
