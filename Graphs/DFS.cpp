#include <stack>
#include <vector>
#include <iostream>

void DFSRecursive(int vertex, const std::vector<std::vector<int>>& graph, std::vector<bool>& visitedVertices)
{
    std::cout << " -> " << vertex + 1;
    visitedVertices.at(vertex) = true;
    for (std::size_t i = 0; i < graph.at(vertex).size(); i++)
        if ((graph.at(vertex).at(i) != 0) && (!visitedVertices.at(i)))
            DFSRecursive(i, graph, visitedVertices);
}

void DFSNonRecursive(int startVertex, const std::vector<std::vector<int>>& graph, std::vector<bool>& visitedVertices)
{
    std::stack<int> stack;
    stack.push(startVertex);
    while (!stack.empty())
    {
        int currentVertex = stack.top();
        std::cout << " -> " << currentVertex + 1;
        stack.pop();
        for (size_t i = 0; i < graph.at(currentVertex).size(); i++) 
        {
            if ((graph.at(currentVertex).at(i) != 0) && (!visitedVertices.at(i)))
            {
                visitedVertices.at(i) = true;
                stack.push(i);
            }
        }
    }
}

int main()
{
    const int startVertex = 0; // start from 0 index
    std::vector<bool> visitedVertices = { false, false, false, false, false };
    const std::vector<std::vector<int>> graph = { 
        // Adjacency matrix
        { 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 0 },
        { 1, 0, 1, 0, 1 },
        { 0, 1, 0, 1, 0 }
    };

    std::cout << "Recursive DFS: ";
    DFSRecursive(startVertex, graph, visitedVertices);
    std::fill(visitedVertices.begin(), visitedVertices.end(), false);
    std::cout << "\nNon recursive DFS: ";
    DFSNonRecursive(startVertex, graph, visitedVertices);

    return EXIT_SUCCESS;
}