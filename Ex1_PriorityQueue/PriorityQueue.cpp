#include <iostream>
#include <iomanip>
#include "PriorityQueue.hpp"

//do zmiany 1, 0 na Tak, Nie
class polish : public std::numpunct<char> {
    protected:
        std::string do_truename() const override {return "Tak";}
        std::string do_falsename() const override {return "Nie";}
};

int main() {
    BinaryHeap<int> heap(10);
    try {
        std::cout.imbue(std::locale(std::locale(), new polish)); //ustawiam locale na wyzej utworzona klase
        std::cout << std::boolalpha; //zamiast 1 0 bedzie wypisywac Tak, Nie
        std::cout << "Czy jest pusta?: "<< heap.IsEmpty() << std::endl;
        heap.Enqueue(5);
        std::cout << "Czy jest pusta?: "<< heap.IsEmpty()<<std::endl;
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.Enqueue(6);
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.Enqueue(8);
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.Enqueue(3);
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.Enqueue(9);
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.Enqueue(2);
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.Enqueue(1);
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;        
        heap.DequeueMin();
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.DequeueMin();  
        heap.display();
        std::cout << "Minimum: "<< heap.FindMin()<<std::endl;
        heap.MakeNull();
        std::cout << "Czy jest pusta?: "<< heap.IsEmpty()<<std::endl;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}