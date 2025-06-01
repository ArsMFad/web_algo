#include "SetGraph.h"

SetGraph::SetGraph(int vertexCount) : adjacencySets(vertexCount) {}


SetGraph::SetGraph(const IGraph& graph) {
    adjacencySets.resize(graph.VerticesCount());
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (int to : graph.GetNextVertices(from)) {
            adjacencySets[from].insert(to);
        }
    }
}


void SetGraph::AddEdge(int from, int to) {
    adjacencySets[from].insert(to);
}


int SetGraph::VerticesCount() const {
    return adjacencySets.size();
}


std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    return std::vector<int>(adjacencySets[vertex].begin(), adjacencySets[vertex].end());
}


std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int from = 0; from < adjacencySets.size(); ++from) {
        if (adjacencySets[from].count(vertex) > 0) {
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
