#include "Graph.hpp"
#include <string_view>

int main(int argc, char* argv[])
{
    if(argc != 2) {
        std::cerr << "Wykonaj program z flaga: -undir albo -dir\n";
        exit(EXIT_FAILURE);
    }

    bool dir;
    if(std::string_view(argv[1]) == "-undir") {
        dir = false;
        std::cout << "\033[1;32m=Wybrano nieskierowany graf=\033[0m\n"; 
    }
    else if(std::string_view(argv[1]) == "-dir") {
        dir = true;
        std::cout << "\033[1;32m==Wybrano skierowany graf==\033[0m\n"; 
    } 
    else {
        std::cerr << "Wykonaj program z flaga: -undir albo -dir";
        exit(EXIT_FAILURE);
    }    

    std::cout <<  "\033[1;32m-------Pierwsza część-------\033[0m" << std::endl;

    GraphAsMatrix g(10, dir);
    std::cout << "Number of Verticies: " << g.NumberOfVertices() << std::endl;
    std::cout << "Number of Edges: " << g.NumberOfEdges() << std::endl;
    std::cout << "--------------------\n";

    Vertex* v = g.SelectVertex(2);
    std::cout << "Select vertex(2) = " << v->Number() << std::endl;
    v->weight = v->Number() * v->Number();
    std::cout << "Weight = " << v->weight << std::endl;
    std::cout << "--------------------\n";

    g.AddEdge(1,2);
    g.AddEdge(1,2);
    g.AddEdge(2,3);
    g.AddEdge(3,4);
    g.AddEdge(9,9);

    std::cout << "Number of Verticies: " << g.NumberOfVertices() << std::endl;
    std::cout << "Number of Edges: " << g.NumberOfEdges() << std::endl;

    std::cout << "Istnieje krawedz (1,1)?: " << (g.SelectEdge(1,1) != nullptr ? "Tak" : "Nie") << std::endl;
    std::cout << "Istnieje krawedz (1,2)?: " << (g.SelectEdge(1,2) != nullptr ? "Tak" : "Nie") << std::endl;
    std::cout << "Istnieje krawedz (2,1)?: " << (g.SelectEdge(2,1) != nullptr ? "Tak" : "Nie") << std::endl;

    std::cout << "-------E(1,2)-------" << std::endl;
    Edge* e = g.SelectEdge(1,2);
    std::cout << *e->V0() << std::endl;
    std::cout << *e->V1() << std::endl;
    std::cout << *e->Mate(e->V0()) << std::endl;
    std::cout << *e->Mate(e->V1()) << std::endl;

    e->weight = e->V0()->Number() + e->V1()->Number();
    std::cout << e->weight << std::endl;

    std::cout << "-------E(2,3)-------" << std::endl;
    e = g.SelectEdge(2,3);
    std::cout << *e->V0() << std::endl;
    std::cout << *e->V1() << std::endl;
    std::cout << *e->Mate(e->V0()) << std::endl;
    std::cout << *e->Mate(e->V1()) << std::endl;

    e->weight = e->V0()->Number() + e->V1()->Number();
    std::cout << e->weight << std::endl;
    std::cout << "-------E(3,4)-------" << std::endl;
    e = g.SelectEdge(3,4);
    std::cout << *e->V0() << std::endl;
    std::cout << *e->V1() << std::endl;
    std::cout << *e->Mate(e->V0()) << std::endl;
    std::cout << *e->Mate(e->V1()) << std::endl;

    e->weight = e->V0()->Number() + e->V1()->Number();
    std::cout << e->weight << std::endl;
    std::cout << "-------E(9,9)-------" << std::endl;
    e = g.SelectEdge(9,9);
    std::cout << *e->V0() << std::endl;
    std::cout << *e->V1() << std::endl;
    std::cout << *e->Mate(e->V0()) << std::endl;
    std::cout << *e->Mate(e->V1()) << std::endl;

    e->weight = e->V0()->Number() + e->V1()->Number();
    std::cout << e->weight << std::endl;

    std::cout <<  "\033[1;32m-------Druga część-------\033[0m" << std::endl;

    g.print_verticies();
 
    std::cout << "--------------------\n";

    g.AddEdge(3,5);
    g.AddEdge(8,3);
    g.AddEdge(5,2);

    g.print_edges();
 
    std::cout << "--------------------\n";

    g.print_em_edges(3);
 
    std::cout << "--------------------\n";

    g.print_in_edges(2);
 
    std::cout << "--------------------\n";

    exit(EXIT_SUCCESS);
}