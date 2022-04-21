#include <iostream>
#include <vector>

class Vertex
{
    private:
        int number{-1};
    public:
        int weight{0};
        std::string label{"EMPTY"};
        Vertex(int n) : number{n} {}
        int Number() const { return number; };

        friend bool operator==(const Vertex& v0, const Vertex& v1) { return v0.number == v1.number; } 
        friend std::ostream& operator<<(std::ostream& ost, Vertex const& v)
        {
            ost << v.number;
            return ost;
        }
};

class Edge
{
    protected:
        Vertex* v0;
        Vertex* v1;
    public:
        int weight{0};
        std::string label{"EMPTY"};
        Edge(Vertex* V0, Vertex* V1) : v0{V0}, v1{V1} {}
        Vertex* V0() { return v0; }
        Vertex* V1() { return v1; }
        Vertex* Mate(Vertex* v) { return v == v0 ? v1 : v0; }
};

template <typename T>
class Iterator
{
    public:
        Iterator(){;}
        virtual ~Iterator(){}
        virtual bool IsDone() const = 0;
        virtual T& operator*() = 0;
        virtual void operator++() = 0;
};

class GraphAsMatrix
{
    private:
        std::vector<Vertex*> vertices;
        std::vector<std::vector<Edge*>> adjacencyMatrix;
        bool isDirected;
        int numberOfVertices = 9;
        int numberOfEdges = 0;

    class AllVerticesIter: public Iterator<Vertex>
    {
        private:
            GraphAsMatrix& owner;
            int current{0};
        public:
            AllVerticesIter(GraphAsMatrix& owner): owner(owner) {};
            bool IsDone() const { return current >= owner.numberOfVertices; }
            Vertex& operator*() { return *(owner.vertices[current]); }
            void operator++() { ++current; }
    };
    class AllEdgesIter: public Iterator<Edge>
    {
        private:
            GraphAsMatrix& owner;
            int row, col;
            bool end = false;
        public:
            void next()
            {
                for(; row < owner.numberOfVertices; row++) {
                    for(++col; col < owner.numberOfVertices; col++) {
                        if(owner.adjacencyMatrix[row][col] != nullptr) 
                            return;
                    }
                    col = -1;
                }
                end = true;
            }
            AllEdgesIter(GraphAsMatrix& owner): owner(owner), row{0}, col{0} { next(); }
            bool IsDone() const { return end; }
            Edge& operator*() { return *owner.SelectEdge(row,col); }
            void operator++(){ next(); }
    };
    class EmanEdgesIter: public Iterator<Edge>
    {
        private:
            GraphAsMatrix& owner;
            int row;
            int col;
            bool end = false;
        public:
            void next()
            {
                for(++col; col < owner.numberOfVertices; col++) {
                    if(owner.adjacencyMatrix[row][col] != nullptr)
                        return;
                }
                end = true;
            }
            EmanEdgesIter(GraphAsMatrix& owner, int u): owner(owner), row{u}, col{-1} { next(); }
            bool IsDone() const { return end; }
            Edge& operator*() { return *owner.SelectEdge(row,col); }
            void operator++() { next(); }
    };
    class InciEdgesIter: public Iterator<Edge>
    {
        private:
            GraphAsMatrix& owner;
            int row;
            int col;
            bool end = false;
        public:
            void next()
            {
                for(++row; row < owner.numberOfVertices; row++) {
                    if(owner.adjacencyMatrix[row][col] != nullptr)
                        return;
                }
                end = true;
            }
            InciEdgesIter(GraphAsMatrix& owner, int v): owner(owner), row{-1}, col{v} { next(); } 
            bool IsDone() const { return end; }
            Edge& operator*() { return *owner.SelectEdge(row,col); }
            void operator++(){ next(); }
    };

    public:
        GraphAsMatrix(int n, bool directed) : numberOfVertices{n}, isDirected{directed} 
        {
            for(int i = 0; i<n; i++) {
                vertices.push_back(new Vertex(i));
                adjacencyMatrix.push_back(std::vector<Edge*>(n, nullptr));
            }
        }
        bool IsDirected() { return isDirected; }
        int NumberOfVertices() { return numberOfVertices; }
        int NumberOfEdges() { return numberOfEdges; }
        bool IsEdge(int u, int v)
        {
            return adjacencyMatrix[u][v] != nullptr;
        }
        void MakeNull()
        {
            for(int i = 0; i<numberOfVertices; i++) {
                for(int j = 0; j<numberOfVertices; j++) {
                    if(adjacencyMatrix[i][j]) delete adjacencyMatrix[i][j];
                }
            }
            numberOfEdges = 0;
        }
        void AddEdge(int u, int v)
        {
            if(!adjacencyMatrix[u][v]) {
                adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
                numberOfEdges++;
            } 
            if(!isDirected && !adjacencyMatrix[v][u]) {
                adjacencyMatrix[v][u] = new Edge(vertices[v], vertices[u]);
            }   
        }
        void AddEdge(Edge* edge)
        {
            int u = edge->V0()->Number();
            int v = edge->V1()->Number();
            if(!adjacencyMatrix[u][v]) {
                adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
                numberOfEdges++;
            } 
            if(!isDirected && !adjacencyMatrix[v][u]) {
                adjacencyMatrix[v][u] = new Edge(vertices[v], vertices[u]);
            }   

        }
        Edge* SelectEdge (int u, int v) { return adjacencyMatrix[u][v]; }
        Vertex* SelectVertex(int v) { return vertices[v]; }

        void debug()
        {
            for(int i = 0; i<numberOfVertices; i++) {
                for(int j = 0; j<numberOfVertices; j++) {
                    std::cout << (adjacencyMatrix[i][j] == nullptr ? "0" : "1") << " ";
                }
                std::cout << std::endl;
            }
        }

        Iterator<Vertex>& VerticesIter() { return *(new AllVerticesIter(*this)); }
        Iterator<Edge>& EdgesIter() { return *(new AllEdgesIter(*this)); }
        Iterator<Edge>& EmanatingEdgesIter(int u) { return *(new EmanEdgesIter(*this, u)); }
        Iterator<Edge>& IncidentEdgesIter(int v) { return *(new InciEdgesIter(*this, v)); }

        void print_verticies()
        {
            auto& v_it = VerticesIter();
            std::cout << "Verticies:\n";
            while(!v_it.IsDone()) {
                std::cout << "number = " << (*v_it).Number() << " | waga = " << (*v_it).weight << std::endl;
                ++v_it;
            }
        }

        void print_edges()
        {
            auto& e_it = EdgesIter();
            std::cout << "Edges:" << std::endl;
            while(!e_it.IsDone()) {
                std::cout << "v0 = " << (*e_it).V0()->Number() << " " <<  "| v1 = " << (*e_it).V1()->Number() << std::endl;
                ++e_it;
            }
        }

        void print_em_edges(int u)
        {
            auto& ee_it = EmanatingEdgesIter(u);
            std::cout << "Edges, wiersz " << u << std::endl;
            while(!ee_it.IsDone()) {
                std::cout << "v0 = " << (*ee_it).V0()->Number() << " " <<  "| v1 = " << (*ee_it).V1()->Number() << std::endl;
                ++ee_it;
            }
        }

        void print_in_edges(int v)
        {
            auto& ie_it = IncidentEdgesIter(v);
            std::cout << "Edges, kolumna " << v << std::endl;
            while(!ie_it.IsDone()) {
                std::cout << "v0 = " << (*ie_it).V0()->Number() << " " <<  "| v1 = " << (*ie_it).V1()->Number() << std::endl;
                ++ie_it;
            }
        }
};