#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <unordered_map>

class NTimesNMatrix
{
public:
	NTimesNMatrix(size_t n, unsigned defaultValue) : values_(n*n, defaultValue), n_(n) {}
	unsigned& get(unsigned row, unsigned column) { return values_[n_*row + column];}
	size_t getN() const {return n_;}

private:
	std::vector<unsigned> values_;
	size_t n_;
};

class Graph
{
public:
	void addEdge(unsigned from, unsigned to);
	NTimesNMatrix floydWarshall() const;
	

private:
	std::vector<std::vector<unsigned>> adjList_;
};

void Graph::addEdge(unsigned from, unsigned to)
{
	const size_t neededSize = std::max<size_t>(adjList_.size(), from + 1);
	adjList_.resize(neededSize);
	
	adjList_[from].push_back(to);
}

NTimesNMatrix Graph::floydWarshall() const 
{
	const size_t numberOfNodes = adjList_.size();
	NTimesNMatrix distances(numberOfNodes, std::numeric_limits<unsigned>::max() / 4);
	for(size_t i = 0; i < numberOfNodes; ++i)
	{
		distances.get(i,i) = 0;
	}
	
	for (size_t from = 0; from < numberOfNodes; ++from)
	{
		for (auto to : adjList_[from])
			distances.get(from, to) = 1;
	}
	
	for (size_t includedNode = 0; includedNode < numberOfNodes; ++includedNode)
	{
		for (size_t from = 0; from < numberOfNodes; ++from)
		{
			for (size_t to = 0; to < numberOfNodes; ++to)
			{
				const unsigned detourWeight = 
					distances.get(from, includedNode) + distances.get(includedNode, to);
				unsigned& fromToWeight = 
					distances.get(from, to);
				if (detourWeight < fromToWeight)
					fromToWeight = detourWeight;
			}		
		}	
	}
	return distances;
}

double calcAvgWeight(NTimesNMatrix& weights)
{
	double result = 0;
	const size_t n = weights.getN();
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			result += weights.get(i,j);
		}
	}
	return result / (n*n - n);
}


void solveTestcase(const Graph& graph, unsigned testcaseNumber)
{
	NTimesNMatrix weights = graph.floydWarshall();
	const double avgWeight = calcAvgWeight(weights);
	std::cout << "Case " << testcaseNumber << ": average length between pages = " << avgWeight << " clicks\n";
}

unsigned lookupIntern(std::unordered_map<unsigned, unsigned>& extern2intern, unsigned externValue, unsigned& nextIntern)
{
	auto findResult = extern2intern.find(externValue);
	if (findResult == extern2intern.end())
	{
		extern2intern.insert(std::make_pair(externValue, nextIntern));
		return nextIntern++;		
	}
	else
		return findResult->second;
}

bool parseAndSolveTestcase(unsigned testcaseNumber)
{
	Graph graph;
	std::unordered_map<unsigned, unsigned> extern2intern;
	unsigned nextIntern = 0;
	
	unsigned from, to;
	unsigned parsedEdges = 0;
	while (std::cin >> from >> to && ((from != 0) & (to != 0)))
	{
		++parsedEdges;
		
		const unsigned fromIntern = lookupIntern(extern2intern, from, nextIntern);
		const unsigned toIntern = lookupIntern(extern2intern, to, nextIntern);

		graph.addEdge(fromIntern, toIntern);
	} 
	if (parsedEdges == 0)
		return false;
		
	solveTestcase(graph, testcaseNumber);
	return true;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::setprecision(3) << std::fixed;
	
	unsigned testcaseNumber = 1;
	while(parseAndSolveTestcase(testcaseNumber))
	{
		++testcaseNumber;
	}
	return 0;
}
