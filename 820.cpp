#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Matrix
{
public:
	Matrix(size_t numRows, size_t numColumns)
	: numColumns_(numColumns)
	, data_(numRows * numColumns, 0u)
	{}

	int& at(size_t rowPos, size_t columnPos)
	{
		return data_[rowPos * numColumns_ + columnPos];
	}

	int at(size_t rowPos, size_t columnPos) const
	{
		return data_[rowPos * numColumns_ + columnPos];
	}

	size_t getNumRows() const
	{
		return data_.size() / numColumns_;
	}

	size_t getNumColumns() const
	{
		return numColumns_;
	}

private:
	size_t numColumns_;
	vector<int> data_;
};

class Graph
{
public:
	explicit Graph(size_t numNodes)
	: capacityMatrix_(numNodes, numNodes)
	{}

	void addUndirectedCapacity(size_t a, size_t b, int capacity)
	{
		// There may be more than one edge...
		capacityMatrix_.at(a, b) += capacity;
		capacityMatrix_.at(b, a) += capacity;
	}

	int findMaxFlow(size_t s, size_t t)
	{
		Matrix flowMatrix(getNumNodes(), getNumNodes());
		while (true)
		{
			vector<size_t> stPathPred = findPath(s, t, flowMatrix);
			if (stPathPred[t] == numeric_limits<size_t>::max())
				return calculateResult(t, flowMatrix);

			int maxNewFlow = numeric_limits<int>::max();
			for (size_t curr = t; curr != stPathPred[curr]; curr = stPathPred[curr])
			{
				const int capacity = capacityMatrix_.at(stPathPred[curr], curr);
				const int flow = flowMatrix.at(stPathPred[curr], curr);
				maxNewFlow = min(maxNewFlow, capacity - flow);
			}

			for (size_t curr = t; curr != stPathPred[curr]; curr = stPathPred[curr])
			{
				flowMatrix.at(stPathPred[curr], curr) += maxNewFlow;
				flowMatrix.at(curr, stPathPred[curr]) -= maxNewFlow;
			}
		}
	}

private:
	size_t getNumNodes() const
	{
		return capacityMatrix_.getNumColumns();
	}

	vector<size_t> findPath(size_t start, size_t end, const Matrix& flowMatrix)
	{
		vector<size_t> pred(getNumNodes(), numeric_limits<size_t>::max());
		pred[start] = start;

		queue<size_t> q;
		q.push(start);

		while (pred[end] == numeric_limits<size_t>::max() && !q.empty())
		{
			const size_t thisNode = q.front();
			q.pop();
			for (size_t i = 0; i < getNumNodes(); ++i)
			{
				if (pred[i] != numeric_limits<size_t>::max())
					continue;

				const int capacity = capacityMatrix_.at(thisNode, i);
				const int flow = flowMatrix.at(thisNode, i);
				if (flow < capacity)
				{
					pred[i] = thisNode;
					q.push(i);
				}
			}
		}
		return pred;
	}

	static int calculateResult(size_t t, Matrix& flowMatrix)
	{
		int flow = 0;
		for (size_t i = 0; i < flowMatrix.getNumColumns(); ++i)
		{
			flow += flowMatrix.at(i, t);
		}
		return flow;
	}

private:
	Matrix capacityMatrix_;
};

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

	size_t networkNumber = 0;
	size_t n;
	while (cin >> n && n != 0)
	{
		++networkNumber;
		Graph g(n);
		size_t s, t, numEdges;
		cin >> s >> t >> numEdges;
		for (size_t i = 0; i < numEdges; ++i)
		{
			size_t from, to;
			int c;
			cin >> from >> to >> c;
			g.addUndirectedCapacity(from - 1, to - 1, c);
		}
		cout << "Network " << networkNumber << '\n';
		cout << "The bandwidth is " << g.findMaxFlow(s - 1 , t - 1) << ".\n\n";
	}

return 0;
}
