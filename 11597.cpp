#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // In a complete graph with n vertices every vertex has degree n - 1.
    // If we take 2 nodes from a complete graph, we can always construct a
    // Hamiltonian-path from one node to the other. Removing the edges of the
    // path leaves those two nodes with 1 degree less, an even degree,
    // and every other node with 2 degree less, an odd degree.
    // Picking again two nodes with odd degree, we can construct a
    // Hamiltonian-path again. We can do this n / 2 times.
    unsigned numNodes;
    unsigned caseNumber = 1;
    while (cin >> numNodes && numNodes != 0)
    {

        cout << "Case " << caseNumber << ": " << numNodes / 2 << '\n';
        caseNumber++;
    }

}
