#include <queue>
#include <vector>
#include <iostream>

void BFSNonRecursive(int startVertex, const std::vector<std::vector<int>>& graph, std::vector<bool>& visitedVertices)
{
    std::queue<int> queue;
    queue.push(startVertex);
    while (!queue.empty())
    {
        const int currentVertex = queue.front();
        std::cout << " -> " << currentVertex + 1;
        queue.pop();
        for (std::size_t i = 0; i < graph.at(currentVertex).size(); i++) 
        {
            if ( (graph.at(currentVertex).at(i) != 0) && (!visitedVertices.at(i)) ) 
            {
                visitedVertices.at(i) = true;
                queue.push(i);
            }
        }
    }
}

int main()
{
    const int startVertex = 0; // start from 0 index
    std::vector<bool> visitedVertices = { false, false, false, false, false, false };
    const std::vector<std::vector<int>> graph = {
        // Adjacency matrix
        { 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 1, 0 },
        { 1, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 0, 0 }
    };

    std::cout << "Non recursive BFS: ";
    BFSNonRecursive(startVertex, graph, visitedVertices);

    return EXIT_SUCCESS;
}