#include <iostream>
#include <iomanip>
#include "SetAsArray.hpp"

//do zmiany 1, 0 na Tak, Nie
class polish : public std::numpunct<char> {
    protected:
        std::string do_truename() const override {return "\033[32mTak\033[0m";}
        std::string do_falsename() const override {return "\033[31mNie\033[0m";}
};

int main()
{
    std::cout.imbue(std::locale(std::locale(), new polish)); //ustawiam locale na wyzej utworzona klase
    std::cout << std::boolalpha;
    SetAsArray A(10), B(10), C(10), D(10), E(10);

    for(int i = 0; i<10; i++) 
        !(i % 2) ? A.Insert(i) : B.Insert(i);
    
    try {
        //?-----1------
        C = A+B;
        D = C-B;
        std::cout << "A = " << A << std::endl;
        std::cout << "B = " << B << std::endl;
        std::cout << "C = " << C << std::endl;
        std::cout << "D = " << D << std::endl;

        std::cout << "D == A: " << (D == A) << std::endl;
        std::cout << "D <= A: " << (D <= A) << std::endl;
        std::cout << "C == B: " << (C == B) << std::endl;
        std::cout << "B <= C: " << (B <= C) << std::endl;
        A.Insert(1);
        std::cout << "D == A: " << (D == A) << std::endl;
        std::cout << "D <= A: " << (D <= A) << std::endl;

        //?-----2------

        A.Insert(5);
        AddingVisitor av;   
        A.Accept(av);
        E = A * B;
        std::cout << "Suma A = " << av.Result() << std::endl;
        E.Accept(av);
        std::cout << "Suma E = " << av.Result() << std::endl;
        E.Withdraw(1);
        E.Accept(av);
        std::cout << "Suma E = " << av.Result() << std::endl;
        
    } catch(std::out_of_range& ofr) {
        std::cout << ofr.what() << std::endl;
    }
}