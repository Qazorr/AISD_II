#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <memory>

#include "Graph.hpp"

int main()
{
    std::ifstream in, out;

    int x = 0, n, num, broken, expected, loop=1;
    for(const auto &file : std::filesystem::directory_iterator("./testy/")) {
        if(!x) {
            in.open(file.path());
            std::cout << "[" << loop << "] " << file.path() << std::endl;
        }
        else {
            out.open(file.path());
            std::cout << "[" << loop << "] " << file.path() << std::endl;
            in >> n;
            auto graph = std::unique_ptr<GraphAsMatrix>(new GraphAsMatrix(n, false));
            for(int i = 0; i<n; i++) {
                in >> num;
                graph->AddEdge(i, num-1);
            }
            out >> expected;
            broken = graph->piggy_banks(false);
            std::cout << "[" << loop << "] " << (broken == expected ? "\033[32mValid\033[0m" : "\033[31mInvalid\033[0m") << std::endl; 
            in.close();
            out.close();
            loop++;
        }
        x = (x+1) % 2;
    }
}