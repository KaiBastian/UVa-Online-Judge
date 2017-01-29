#include <utility>
#include <vector>
#include <unordered_map>

template<typename ValueType>
class PriorityQueue
{
public:
using PrioType = unsigned; //lower is better
using StoredType = std::pair<ValueType, PrioType>;
	
	PriorityQueue();
	void push(StoredType);
	void pop();
	StoredType top();
	void update(StoredType);
	void updateOrPush(StoredType);
	PrioType getPrio(ValueType);
		
	bool empty() {return heap_.size() == 1;}
	
private:
using HeapLocationType = unsigned;
	HeapLocationType lastElement();
	HeapLocationType firstElement();
	void swap(HeapLocationType, HeapLocationType);
	void bubbleUp(HeapLocationType);
	void bubbleDown(HeapLocationType);
	HeapLocationType getParent(HeapLocationType);
	HeapLocationType getSmallerChild(HeapLocationType);
	
private:
	std::vector<StoredType> heap_; //indexed starting w/1 bc of getParent w/o branching
	std::unordered_map<ValueType, HeapLocationType> value2Pos_;
};

template<typename ValueType>
PriorityQueue<ValueType>::PriorityQueue()
{
	heap_.push_back(std::make_pair(ValueType(), PrioType()));
}

template<typename ValueType>
void PriorityQueue<ValueType>::push(StoredType element)
{
	heap_.push_back(element);
	const auto newElementPos = lastElement();
	value2Pos_.insert(std::make_pair(element.first, newElementPos));
	bubbleUp(newElementPos);
}

template<typename ValueType>
void PriorityQueue<ValueType>::pop()
{
	if (heap_.empty())
		return;
		
	const auto lastPos = lastElement();
	swap(firstElement(), lastPos);
	heap_.pop_back();
	bubbleDown(firstElement());
}

template<typename ValueType>
typename PriorityQueue<ValueType>::StoredType 
PriorityQueue<ValueType>::top()
{
	if (heap_.empty())
		return std::make_pair(ValueType(), PrioType());
	
	return heap_[firstElement()];		
}

template<typename ValueType>
void PriorityQueue<ValueType>::update(StoredType element)
{
	const HeapLocationType pos = value2Pos_[element.first];
	heap_[pos].second = element.second;
	bubbleUp(pos);
}

template<typename ValueType>
void PriorityQueue<ValueType>::updateOrPush(StoredType element)
{
	const auto findResult = value2Pos_.find(element.first);
	if (findResult == value2Pos_.end())
		push(element);
	else
		update(element);
}

template<typename ValueType>
typename PriorityQueue<ValueType>::PrioType 
PriorityQueue<ValueType>::getPrio(ValueType elem)
{
	HeapLocationType elemPos = value2Pos_.find(elem)->second;
	return heap_[elemPos].second;
}

template<typename ValueType>
typename PriorityQueue<ValueType>::HeapLocationType 
PriorityQueue<ValueType>::lastElement()
{
	return static_cast<HeapLocationType>(heap_.size() - 1);
}

template<typename ValueType>
typename PriorityQueue<ValueType>::HeapLocationType 
PriorityQueue<ValueType>::firstElement()
{
	HeapLocationType first {1};
	return first;
}

template<typename ValueType>
void PriorityQueue<ValueType>::swap(HeapLocationType a, HeapLocationType b)
{
	StoredType storedA = heap_[a];
	StoredType storedB = heap_[b];
	value2Pos_.find(storedA.first)->second = b;
	value2Pos_.find(storedB.first)->second = a;
		
	std::swap(heap_[a], heap_[b]);	
}
	
template<typename ValueType>
void PriorityQueue<ValueType>::bubbleUp(HeapLocationType start)
{
	for (HeapLocationType current = start , parent = getParent(start);
		 current != parent;
		 current = parent, parent = getParent(current))
	{
		const PrioType currentPrio = heap_[current].second;
		const PrioType parentPrio = heap_[parent].second;
		const bool notInOrder = currentPrio < parentPrio;
		if (notInOrder)
			swap(parent, current);
		else
			break;
	}		 
}
	
template<typename ValueType>
void PriorityQueue<ValueType>::bubbleDown(HeapLocationType start)
{
	for (HeapLocationType current = start, smallerChild = getSmallerChild(start);
		 smallerChild < lastElement();
		 current = smallerChild, smallerChild = getSmallerChild(smallerChild))
	{
		const PrioType currentPrio = heap_[current].second;
		const PrioType smallerChildPrio = heap_[smallerChild].second;
		const bool notInOrder = currentPrio > smallerChildPrio;
		if (notInOrder)
			swap(current, smallerChild);
		else
			break;
	}
}

template<typename ValueType>
typename PriorityQueue<ValueType>::HeapLocationType 
PriorityQueue<ValueType>::getParent(HeapLocationType element)
{
	// As we index starting with 1 an element at pos i has the children
    // 2*i and 2*i + 1. As this function is supposed to map 0 to 0, we 
    // don't need to branch here.
	return element / 2;
}
	
template<typename ValueType>
typename PriorityQueue<ValueType>::HeapLocationType 
PriorityQueue<ValueType>::getSmallerChild(HeapLocationType element)
{
	// i has children i*2 and i*2 + 1 beause we to index starting w/1.
	const HeapLocationType left = element*2;
	const HeapLocationType right = element*2 + 1;
	const PrioType leftPrio = heap_[left].second;
	const PrioType rightPrio = heap_[right].second;
	if (leftPrio < rightPrio)
		return left;
	else
		return right;
}

#include <vector>
#include <list>
#include <utility>
#include <limits>
#include <deque>

class Graph
{
public:
	using NodeType = unsigned;
	using WeightType = unsigned;
	
	Graph(NodeType numberOfNodes);
	void addEdge(NodeType from, NodeType to, WeightType weight);
	WeightType singleSourceShortesPath(NodeType from, NodeType to, std::deque<NodeType>& route);
	
private:
	NodeType dummyNode();
	void calculateRoute(NodeType from, NodeType to, 
		const std::vector<NodeType>& predecessors, 
		std::deque<NodeType>& route);
	
private:
	std::vector<std::list<std::pair<NodeType,WeightType>>> adjacencyLists_;
};

Graph::Graph(Graph::NodeType node)
{
	const std::size_t vectorSize = static_cast<std::size_t>(node);
	adjacencyLists_.resize(vectorSize);
}

void Graph::addEdge(Graph::NodeType from, Graph::NodeType to, Graph::WeightType weight)
{
	adjacencyLists_[from].push_back(std::make_pair(to, weight));
}

Graph::WeightType Graph::singleSourceShortesPath(
	Graph::NodeType from, Graph::NodeType to, std::deque<Graph::NodeType>& route)
{
		std::vector<NodeType> predecessors;
		const size_t numberOfNodes = adjacencyLists_.size();
		predecessors.resize(numberOfNodes, dummyNode());		
		predecessors[from] = from;

		const WeightType maxWeight = std::numeric_limits<WeightType>::max();
		std::vector<WeightType> weights;
		weights.reserve(adjacencyLists_.size());
		for (size_t i = 0; i < adjacencyLists_.size(); ++i)
		{
			const WeightType prio = i == from ? 0 : maxWeight;
			weights.push_back(prio);
		}
		
		PriorityQueue<NodeType> unvisitedNodes; // TODO reserve
		unvisitedNodes.push(std::make_pair(from, 0));
		
		while (!unvisitedNodes.empty())
		{
			const auto queueContent = unvisitedNodes.top();
			unvisitedNodes.pop();
			const NodeType node = queueContent.first;
			const WeightType sourceWeight = queueContent.second;
			
			// enqueue all reachable
			const auto adjacencyList = adjacencyLists_[node];
			for (const auto edge : adjacencyList)
			{
				const NodeType targetNode = edge.first;
				const WeightType targetWeight = weights[targetNode];
				const WeightType newWeight = sourceWeight + edge.second;
				if (newWeight < targetWeight)
				{
					unvisitedNodes.updateOrPush(std::make_pair(targetNode, newWeight));
					predecessors[targetNode] = node;
					weights[targetNode] = newWeight;
				}
			}			
		}
		
		calculateRoute(from, to, predecessors, route);
		
		return weights[to];
		
}

Graph::NodeType Graph::dummyNode()
{
	return std::numeric_limits<NodeType>::max();
}

void Graph::calculateRoute(
	NodeType from, NodeType to, const std::vector<NodeType>& predecessors, 
	std::deque<NodeType>& route)
{
	for (NodeType currentNode = to; currentNode != from; currentNode = predecessors[currentNode])
	{
		route.push_front(currentNode);
	}
	route.push_front(from);
}
	

#include <iostream>	
	
int main()
{

unsigned caseNumber = 0;
unsigned numberOfIntersections;
while (true)
{
	caseNumber++;
	
	std::cin >> numberOfIntersections;
	if (numberOfIntersections == 0)
		break;
		
	Graph graph(numberOfIntersections);
	
	for (unsigned from = 1; from <= numberOfIntersections; ++from)
	{
		unsigned numberOfRoads;
		std::cin >> numberOfRoads;
		while (numberOfRoads-- > 0)
		{
			unsigned target;
			unsigned weight;
			std::cin >> target >> weight;
			graph.addEdge(from - 1, target - 1, weight);
		}
	}
	
	unsigned from, to;
	std::cin >> from >> to;
	
	std::deque<unsigned> route;
	const unsigned weight = graph.singleSourceShortesPath(from - 1, to - 1, route);
	
	std::cout << "Case " << caseNumber << ": Path =";
	for (auto node : route)
	{
		std::cout << ' ' << node + 1;
	}
	std::cout << "; " << weight << " second delay\n";	
}	
	
}

	
