#include <queue>
#include <vector>
#include <iostream>

template<typename T>
void bfs_non_recursive(T start_vertex, const std::vector<std::vector<T>>& graph, std::vector<bool>& visited_vertices) noexcept
{
    std::queue<T> queue;
    queue.push(start_vertex);
    while (!queue.empty())
    {
        const T currentVertex = queue.front();
        std::cout << " -> " << currentVertex + 1;
        queue.pop();
        for (std::size_t i = 0; i < graph.size(); i++) 
        {
            if ( (graph.at(currentVertex).at(i) != 0) && (!visited_vertices.at(i)) )
            {
                visited_vertices.at(i) = true;
                queue.push(i);
            }
        }
    }
}

int main()
{
    const std::vector<std::vector<int>> graph = {
        // Adjacency matrix
        { 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 1, 0 },
        { 1, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 0, 0 }
    };

    const int start_vertex = 0;
    std::vector<bool> visited_vertices(graph.size());

    std::cout << "Non recursive BFS: ";
    bfs_non_recursive(start_vertex, graph, visited_vertices);

    return EXIT_SUCCESS;
}