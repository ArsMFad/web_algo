#include "ListGraph.h"


ListGraph::ListGraph(int vertexCount) : adjacencyLists(vertexCount) {}


ListGraph::ListGraph(const IGraph& graph) {
    adjacencyLists.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjacencyLists[i] = graph.GetNextVertices(i);
    }
}


void ListGraph::AddEdge(int from, int to) {
    adjacencyLists[from].push_back(to);
}


int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}


std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return adjacencyLists[vertex];
}


std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int from = 0; from < adjacencyLists.size(); ++from) {
        for (int to : adjacencyLists[from]) {
            if (to == vertex) {
                prevVertices.push_back(from);
                break;
            }
        }
    }
    return prevVertices;
}
