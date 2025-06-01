#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
#include <cassert>

using namespace std;


struct Edge {
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};


struct IGraph {
    virtual ~IGraph() {}
    
    virtual void AddEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const = 0;
    virtual vector<Edge> GetNextEdges(int vertex) const = 0;
};


struct ListGraph : public IGraph {
public:
    ListGraph(int size) : adjacencyLists(size) {}
    
    ~ListGraph() override {}
    
    void AddEdge(int from, int to, int weight) override {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].emplace_back(to, weight);
    }
    
    int VerticesCount() const override {
        return static_cast<int>(adjacencyLists.size());
    }
    
    vector<Edge> GetNextEdges(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    
private:
    vector<vector<Edge>> adjacencyLists;
};


int findShortestPath(const IGraph& graph, int start, int end) {
    int verticesCount = graph.VerticesCount();
    if (start < 0 || start >= verticesCount || end < 0 || end >= verticesCount) {
        return -1;
    }

    vector<int> distances(verticesCount, INT_MAX);
    distances[start] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentVertex = pq.top().second;
        pq.pop();

        if (currentDist > distances[currentVertex]) {
            continue;
        }

        for (const Edge& edge : graph.GetNextEdges(currentVertex)) {
            int neighbor = edge.to;
            int newDist = currentDist + edge.weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.push({newDist, neighbor});
            }
        }
    }

    return distances[end] == INT_MAX ? -1 : distances[end];
}


void solve(istream &in, ostream &out) {
    int N, M;
    in >> N >> M;

    ListGraph graph(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        graph.AddEdge(u, v, w);
        graph.AddEdge(v, u, w);
    }

    int s, t;
    in >> s >> t;

    int result = findShortestPath(graph, s, t);
    out << result << endl;
}


void test() {
    {
        istringstream in("6 9\n0 3 1\n0 4 2\n1 2 7\n1 3 2\n1 4 3\n1 5 3\n2 5 3\n3 4 4\n3 5 6\n0 2");
        ostringstream out;
        solve(in, out);
        assert(out.str() == "9\n");
    }
    {
        istringstream in("3 2\n0 1 1\n1 2 1\n0 2");
        ostringstream out;
        solve(in, out);
        assert(out.str() == "2\n");
    }
    {
        istringstream in("3 3\n0 1 1\n1 2 1\n0 2 3\n0 2");
        ostringstream out;
        solve(in, out);
        assert(out.str() == "2\n");
    }
    {
        istringstream in("1 0\n0 0");
        ostringstream out;
        solve(in, out);
        assert(out.str() == "0\n");
    }
}


int main() {
    solve(cin, cout);
//    test();
    return 0;
}
