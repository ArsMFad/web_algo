#include <cassert>
#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"


void TestAddEdgeAndVertices(IGraph& graph) {
    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 0);

    assert(graph.VerticesCount() == 4);

    assert(graph.GetNextVertices(0) == std::vector<int>{1});
    assert(graph.GetNextVertices(1) == std::vector<int>{2});
    assert(graph.GetNextVertices(2) == std::vector<int>{0});
    assert(graph.GetNextVertices(3).empty());

    assert(graph.GetPrevVertices(0) == std::vector<int>{2});
    assert(graph.GetPrevVertices(1) == std::vector<int>{0});
    assert(graph.GetPrevVertices(2) == std::vector<int>{1});
    assert(graph.GetPrevVertices(3).empty());
}


void TestCopyConstructor(const IGraph& original) {
    ListGraph listCopy(original);
    MatrixGraph matrixCopy(original);
    SetGraph setCopy(original);
    ArcGraph arcCopy(original);

    for (int i = 0; i < original.VerticesCount(); ++i) {
        assert(original.GetNextVertices(i) == listCopy.GetNextVertices(i));
        assert(original.GetNextVertices(i) == matrixCopy.GetNextVertices(i));
        assert(original.GetNextVertices(i) == setCopy.GetNextVertices(i));
        assert(original.GetNextVertices(i) == arcCopy.GetNextVertices(i));

        assert(original.GetPrevVertices(i) == listCopy.GetPrevVertices(i));
        assert(original.GetPrevVertices(i) == matrixCopy.GetPrevVertices(i));
        assert(original.GetPrevVertices(i) == setCopy.GetPrevVertices(i));
        assert(original.GetPrevVertices(i) == arcCopy.GetPrevVertices(i));
    }
}


int main() {
    {
        ListGraph graph(4);
        TestAddEdgeAndVertices(graph);
        TestCopyConstructor(graph);
        std::cout << "ListGraph tests passed!\n";
    }
    {
        MatrixGraph graph(4);
        TestAddEdgeAndVertices(graph);
        TestCopyConstructor(graph);
        std::cout << "MatrixGraph tests passed!\n";
    }
    {
        SetGraph graph(4);
        TestAddEdgeAndVertices(graph);
        TestCopyConstructor(graph);
        std::cout << "SetGraph tests passed!\n";
    }
    {
        ArcGraph graph(4);
        TestAddEdgeAndVertices(graph);
        TestCopyConstructor(graph);
        std::cout << "ArcGraph tests passed!\n";
    }

    std::cout << "All tests passed!\n";
    return 0;
}
