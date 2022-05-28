#include "Graph.hpp"

int main(int argc, char* argv[])
{
    GraphAsMatrix graph(10, false);
    graph.AddEdge(0,1);
    graph.AddEdge(1,2);
    graph.AddEdge(2,3);
    graph.AddEdge(3,4);
    graph.AddEdge(3,7);
    graph.AddEdge(4,5);
    graph.AddEdge(5,9);
    graph.AddEdge(9,9);
    graph.AddEdge(6,8);
    graph.AddEdge(8,6);
    graph.AddEdge(0,8);
    graph.DFS_Spanning_Tree(graph.SelectVertex(0));
    std::cout << std::endl;
    graph.AddEdge(3,9);
    graph.AddEdge(5,7);
    graph.AddEdge(9,8);
    graph.DFS_Spanning_Tree(graph.SelectVertex(0));
}