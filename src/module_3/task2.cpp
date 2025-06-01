#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>
#include <sstream>


struct IGraph {
    virtual ~IGraph() {}
        
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


struct ListGraph : public IGraph {
public:
    ListGraph(int size) : adjacencyLists(size) {}
    
    ListGraph(const IGraph& graph) {
        adjacencyLists.resize(graph.VerticesCount());
        for (int i = 0; i < graph.VerticesCount(); ++i) {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }
    
    ~ListGraph() override {}
    
    void AddEdge(int from, int to) override {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }
    
    int VerticesCount() const override {
        return static_cast<int>(adjacencyLists.size());
    }
    
    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    
    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        
        for (int from = 0; from < adjacencyLists.size(); ++from) {
            for (int to : adjacencyLists[from]) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }
    
private:
    std::vector<std::vector<int>> adjacencyLists;
};


int countShortestPaths(const IGraph& graph, int start, int end) {
    int verticesCount = graph.VerticesCount();
    if (start < 0 || start >= verticesCount || end < 0 || end >= verticesCount) {
        return 0;
    }

    std::vector<int> distances(verticesCount, -1);
    std::vector<int> counts(verticesCount, 0);
    std::queue<int> queue;

    distances[start] = 0;
    counts[start] = 1;
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int neighbor : graph.GetNextVertices(current)) {
            if (distances[neighbor] == -1) {
                distances[neighbor] = distances[current] + 1;
                counts[neighbor] = counts[current];
                queue.push(neighbor);
            } 
            else if (distances[neighbor] == distances[current] + 1) {
                counts[neighbor] += counts[current];
            }
        }
    }

    return counts[end];
}


void solve(std::istream &in, std::ostream &out) {
    int v, n;
    in >> v >> n;

    ListGraph graph(v);
    for (int i = 0; i < n; ++i) {
        int a, b;
        in >> a >> b;
        graph.AddEdge(a, b);
        graph.AddEdge(b, a);
    }

    int u, w;
    in >> u >> w;

    int result = countShortestPaths(graph, u, w);
    out << result << "\n";
}


void test() {
    {
        std::stringstream in("2 1\n0 1\n0 1");
        std::stringstream out;
        solve(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in("3 2\n0 1\n1 2\n0 2");
        std::stringstream out;
        solve(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in("4 4\n0 1\n0 2\n1 3\n2 3\n0 3");
        std::stringstream out;
        solve(in, out);
        assert(out.str() == "2\n");
    }
    {
        std::stringstream in("3 1\n0 1\n0 2");
        std::stringstream out;
        solve(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in("1 0\n0 0");
        std::stringstream out;
        solve(in, out);
        assert(out.str() == "1\n");
    }
}


int main() {
    solve(std::cin, std::cout);
    //test();

    return 0;
}
