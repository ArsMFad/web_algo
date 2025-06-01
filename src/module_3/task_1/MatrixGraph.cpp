#include "MatrixGraph.h"


MatrixGraph::MatrixGraph(int vertexCount) : adjacencyMatrix(vertexCount, std::vector<bool>(vertexCount, false)) {}


MatrixGraph::MatrixGraph(const IGraph& graph) {
    int vertexCount = graph.VerticesCount();
    adjacencyMatrix.resize(vertexCount, std::vector<bool>(vertexCount, false));
    for (int from = 0; from < vertexCount; ++from) {
        for (int to : graph.GetNextVertices(from)) {
            adjacencyMatrix[from][to] = true;
        }
    }
}


void MatrixGraph::AddEdge(int from, int to) {
    adjacencyMatrix[from][to] = true;
}


int MatrixGraph::VerticesCount() const {
    return adjacencyMatrix.size();
}


std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (int to = 0; to < adjacencyMatrix.size(); ++to) {
        if (adjacencyMatrix[vertex][to]) {
            nextVertices.push_back(to);
        }
    }
    return nextVertices;
}


std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int from = 0; from < adjacencyMatrix.size(); ++from) {
        if (adjacencyMatrix[from][vertex]) {
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
