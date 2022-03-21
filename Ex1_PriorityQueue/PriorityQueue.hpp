#include <vector>

#define DEFAULT_SIZE 128

class Container {
    protected:
        Container() {};
    public:
        virtual unsigned int Count() const = 0;
        virtual bool IsEmpty() const { return Count() == 0; }  
        virtual bool IsFull() const = 0;
        virtual void MakeNull() = 0;
};

template <typename T>
class PriorityQueue : public Container {
    public:
        virtual void Enqueue(T element) = 0;
        virtual T FindMin() const = 0;
        virtual T DequeueMin() = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T> {
    protected:
        int count;
        std::vector<T> data;
    public:
        BinaryHeap() : count{0}, data(DEFAULT_SIZE) {}
        BinaryHeap(unsigned int n) : count{0}, data(n) {} 
        ~BinaryHeap() = default;
        void MakeNull() { count = 0; }
        void Enqueue(T element)
        {
            if (count>=data.size()) //jesli element sie nie miesci, powiekszamy wektor
                data.resize(2*count); 
            int i = count;
            count++;
            while((i>0) && (data[(i-1)/2]>element)) //szukamy gdzie mozemy dodac element
            {
                data[i]=data[(i-1)/2];
                i=(i-1)/2;
            }
            data[i]=element;    //dodajemy element
        }
        T FindMin() const
        {
            if(!IsEmpty()) return data[0];
            throw std::out_of_range("No data");
        }
        T DequeueMin()
        {
            if (count>0)
            {
                T min = data[0]; //zapisuje sobie wartosc ktora potem zwroce (minimum w heapie)
                T last = data[count-1];
                count--;
                int i = 0;
                while (2*i + 1 < count) //przesiewanie
                {
                    int child = 2*i + 1;
                    if ((child+1 < count) && (data[child+1] < data[child]))
                        child++;
                    if (last <= data[child])
                        break;
                    data[i] = data[child];
                    i = child;
                }
                data[i] = last;
                return min; //po usunieciu zwracam wartosc
            }
            throw std::out_of_range("No data");
        }
        bool IsEmpty() const { return count == 0; }
        bool IsFull() const { return false; } //nie do konca rozumiem jak ma dzialać ta funkcja
        unsigned int Count() const { return count; }
        void display()
        {
            std::cout << "\tKolejka: ";
            for(int i = 0; i<count; i++) {
                if(i == 0) std::cout << "\033[31m" << data[i] << "\033[0m ";
                else std::cout << "\033[32m" << data[i] << "\033[0m ";
            }
            std::cout << std::endl;
        }
};