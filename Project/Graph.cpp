#include "Graph.hpp"

int main()
{
    int n;
    std::cin >> n;
    GraphAsMatrix graph(n, true);

    int num;
    for(int i = 0; i<n; i++) {
        std::cin >> num;
        graph.AddEdge(i, num-1); 
    }

    graph.piggy_banks();
}