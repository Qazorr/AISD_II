#include <iostream>
#include <vector>

template <typename T>
class Visitor {
    public:
        virtual void Visit(T& element);
        virtual bool IsDone() const { return false; }
};

class PrintVisitor : public Visitor<int> {
    public:
        void Visit(int& element) { std::cout << element << std::endl; }
};

class AddingVisitor : public Visitor<int> {
    private:
        int sum{0};
    public:
        int Result(bool reset = true) 
        { 
            int tmp = sum;
            if(reset) sum = 0;
            return tmp;
        }
        void Visit(int& el) { sum += el; }
};

class OddVisitor : public Visitor<int> {
    private:
        bool odd = false;
    public:
        void Visit(int& element) { if(element % 2) odd = true; }
        bool IsDone() const { return odd; }
        bool OddFound() const { return odd; }
        void Reset() { odd = false; }
};

template <typename T>class Iterator
{
    public:
        Iterator(){;}
        virtual ~Iterator(){}
        virtual bool IsDone()const = 0;
        virtual const T& operator*() = 0;
        virtual void operator++() = 0;
};

template <typename T>
class Container {
    protected:
        Container() {};
    public:
        virtual unsigned int Count() const = 0;
        virtual bool IsEmpty() const { return Count() == 0; }  
        virtual bool IsFull() const = 0;
        virtual void MakeNull() = 0;
        virtual void Accept(Visitor<T>&) const = 0;
};

template <typename T>
class Set : public virtual Container<T>
{
protected:
    int count;
    int universeSize;
public:
    Set(unsigned int n) : count{0}, universeSize(n) {}
    int UniverseSize() const { return universeSize; }
    unsigned int Count() const { return count; }
    virtual void Insert(T element) = 0;
    virtual bool IsMember(T element) const = 0;
    virtual void Withdraw(T element) = 0;
}; 

class SetAsArray : public Set<int> {
    private:
        std::vector<bool> array;

        class Iter:public Iterator<int>
        {
            private:
                std::vector<bool> data;
                int universeSize;
                int index = 0;
            public:
                Iter(std::vector<bool> array, int us) : data(array), universeSize{us} 
                {
                    for(index = 0; index<universeSize; index++) {
                        if(data[index]) break;
                    }
                }
                ~Iter() = default;
                const int& operator*() { return index; }
                void operator++() 
                {
                    for(++index; index < universeSize; index++) {
                        if(data[index]) break;
                    }
                }
                bool IsDone() const { return index == universeSize; }
        };

    public:
        SetAsArray(unsigned int n) : Set(n), array(n, false) {}
        bool IsFull() const { return Count() == UniverseSize(); }
        void MakeNull()
        {
            std::fill(array.begin(), array.end(), false);
            count = 0;
        }
        bool IsMember(int element) const { return array[element]; }
        void Insert(int element)
        {
            if(!IsMember(element)) {
                array[element] = true;
                count++;
            }
        }
        void Withdraw(int element) 
        { 
            if(IsMember(element)) {
                array[element] = false; 
                count--;
            }
        }
        void print()
        {
            int last;
            for(last = UniverseSize()-1; last >= 0, !array[last]; last--);
            std::cout << "Set: {";
            for(int i = 0; i<UniverseSize(); i++) {
                if(array[i]) std::cout << i;
                if(i != last && array[i]) std::cout << ", ";
            }
            std::cout << "}" << std::endl;
        }
        static bool same_universe(SetAsArray const& A, SetAsArray const& B) { return A.UniverseSize() == B.UniverseSize(); }
        friend SetAsArray operator+(SetAsArray const& A, SetAsArray const& B)
        {
            if(!same_universe(A, B)) throw std::out_of_range("Not the same universe");
            SetAsArray to_return(A.UniverseSize());
            for(int i = 0; i<to_return.universeSize; i++) {
                if(A.IsMember(i) || B.IsMember(i))
                    to_return.Insert(i);
            }
            return to_return;
        }
        friend SetAsArray operator-(SetAsArray const& A, SetAsArray const& B)
        {
            if(!same_universe(A, B)) throw std::out_of_range("Not the same universe");
            SetAsArray to_return(A.UniverseSize());
            for(int i = 0; i<to_return.universeSize; i++) {
                if(A.IsMember(i) && !B.IsMember(i))
                    to_return.Insert(i);
            }
            return to_return;
        }
        friend SetAsArray operator*(SetAsArray const& A, SetAsArray const& B)
        {
            if(!same_universe(A, B)) throw std::out_of_range("Not the same universe");
            SetAsArray to_return(A.UniverseSize());
            for(int i = 0; i<to_return.universeSize; i++) {
                if(A.IsMember(i) && B.IsMember(i))
                    to_return.Insert(i);
            }
            return to_return;
        }
        friend bool operator==(SetAsArray const& A, SetAsArray const& B)
        {
            if(!same_universe(A, B)) throw std::out_of_range("Not the same universe");
            for(int i = 0; i<A.UniverseSize(); i++) {
                if((A.IsMember(i) ^ B.IsMember(i)))
                    return false;
            }
            return true;
        }
        friend bool operator<=(SetAsArray const& A, SetAsArray const& B)
        {
            if(!same_universe(A, B)) throw std::out_of_range("Not the same universe");
            for(int i = 0; i<A.UniverseSize(); i++) {
                if(A.IsMember(i) && !B.IsMember(i))
                    return false;
            }
            return true;
        }
        friend std::ostream& operator<<(std::ostream& ost, SetAsArray const& A)
        {
            int last;
            for(last = A.UniverseSize()-1; last >= 0 && !A.array[last]; last--);
            ost << "{";
            if(last == -1) {
                ost << "}";
                return ost;
            }
            for(int i = 0; i<A.UniverseSize(); i++) {
                if(A.array[i]) ost << i;
                if(i != last && A.array[i]) ost << ", ";
            }
            ost << "}";
            return ost;
        }

        Iter & NewIterator() { return * new Iter(array, universeSize); }

        void IteratorPrint()
        {
            Iter &it = NewIterator();
            while(!it.IsDone()) {
                std::cout << *it << " ";
                ++it;
            }
            std::cout << std::endl;
        }

        void Accept(Visitor<int>& v) const {
            for(int i = 0; i<universeSize; i++) {
                if(array[i]) {
                    v.Visit(i);
                    if(v.IsDone()) {
                        std::cout << "\tWizytacja skonczyla sie na komorce \033[32m" << i << "\033[0m\n";
                        return;
                    }
                }
            }
        }
};