#include <iostream>
#include <vector>

class Vertex
{
    private:
        int number{-1};
    public:
        int weight{-1};
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
        int weight{-1};
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
        virtual const T& operator*() = 0;
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
            bool IsDone() { return current >= owner.numberOfVertices; }
            Vertex& operator*() { return *(owner.vertices[current]); }
            void operator++() { ++current; }
    };
    class AllEdgesIter: public Iterator<Edge>
    {
        private:
            GraphAsMatrix& owner;
            int row, col;
        public:
            void next();
            AllEdgesIter(GraphAsMatrix& owner);
            bool IsDone();
            Edge& operator*();
            void operator++(){ next(); }
    };
    class EmanEdgesIter: public Iterator<Edge>
    {
        private:
            GraphAsMatrix& owner;
            int row;
            int col;
            public:
            void next();
            EmanEdgesIter(GraphAsMatrix& owner, int v);
            bool IsDone();
            Edge& operator*();
            void operator++() { next(); }
    };
    class InciEdgesIter: public Iterator<Edge>
    {
        private:
            GraphAsMatrix& owner;
            int row;
            int col;
            void next();
            InciEdgesIter(GraphAsMatrix& owner, int v);
            bool IsDone();
            Edge& operator*();
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
            if(vertices[u] == nullptr) {
                vertices[u] = new Vertex(u);
                numberOfVertices++;
            }

            if(vertices[v] == nullptr) {
                vertices[v] = new Vertex(v);
                numberOfVertices++;
            }
            if(!adjacencyMatrix[u][v]) {
                adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
                numberOfEdges++;
            } 
            if(!isDirected && adjacencyMatrix[v][u]) {
                adjacencyMatrix[v][u] = new Edge(vertices[v], vertices[u]);
            }   
        }
        void AddEdge(Edge* edge)
        {

        }
        Edge* SelectEdge (int u, int v) { return adjacencyMatrix[u][v]; }
        Vertex* SelectVertex(int v) { return vertices[v]; }

        void debug()
        {
            for(int i = 0; i<numberOfVertices; i++) {
                for(int j = 0; j<numberOfVertices; j++) {
                    std::cout << (adjacencyMatrix[i][j] == nullptr ? "o" : "x") << " ";
                }
                std::cout << std::endl;
            }
        }

        Iterator<Vertex>& VerticesIter();
        Iterator<Edge>& EdgesIter();
        Iterator<Edge>& EmanatingEdgesIter(int v);
        Iterator<Edge>& IncidentEdgesIter(int v);
};