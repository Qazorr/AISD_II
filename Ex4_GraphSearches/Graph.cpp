#include "Graph.hpp"
#include <string_view>

class polish : public std::numpunct<char> {
    protected:
        std::string do_truename() const override {return "\033[32mTak\033[0m";}
        std::string do_falsename() const override {return "\033[31mNie\033[0m";}
};


int main(int argc, char* argv[])
{
    std::cout.imbue(std::locale(std::locale(), new polish)); //ustawiam locale na wyzej utworzona klase
    std::cout << std::boolalpha;
    if(argc != 3) {
        std::cerr << "Wykonaj program z flaga: -undir albo -dir + 'dfs'/'spojnosc'\n";
        exit(EXIT_FAILURE);
    }

    bool dir, dfs = false;
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

    if(std::string_view(argv[2]) == "dfs") {
        dfs = true;
        std::cout << "\033[1;32m=Wybrano sprawdzenie DFS=\033[0m\n"; 
    }
    else if(std::string_view(argv[2]) == "spojnosc") {
        dfs = false;
        std::cout << "\033[1;32m==Wybrano sprawdzenie spojnosci==\033[0m\n"; 
    }
    else {
        std::cerr << "Wykonaj program z flaga: -undir albo -dir + 'dfs'/'spojnosc'\n";
        exit(EXIT_FAILURE);
    }

    if(dfs) {
        GraphAsMatrix graph(10, dir);

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
        graph.DFS(graph.SelectVertex(0));
    } else {
        GraphAsMatrix graph(10, dir);
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
        if(dir) {
            graph.AddEdge(0,8);
            graph.AddEdge(6,0);
            graph.AddEdge(9,0);
            std::cout << "graf jest spojny = " << graph.IsConnected()<<std::endl;
            graph.AddEdge(7,0);
            std::cout << "graf jest spojny = " << graph.IsConnected()<<std::endl;
        } else {
            std::cout << "graf jest spojny = " << graph.IsConnected()<<std::endl;
            graph.AddEdge(0,8);
            std::cout << "graf jest spojny = " << graph.IsConnected()<<std::endl;
        }
    }
}