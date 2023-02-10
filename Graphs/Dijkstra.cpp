#include <vector>
#include <iostream>
#include <unordered_set>

int find_vertex_with_min_distance(std::vector<int>& min_distances, std::unordered_set<int>& visited)
{
    int min_vertex_idx = -1;
    int min_distance = std::numeric_limits<int>::max();
    for (int idx = 0; idx < min_distances.size(); ++idx) {
        if (visited.count(idx) != 0)
            continue;

        if (min_distances[idx] <= min_distance) {
            min_distance = min_distances[idx];
            min_vertex_idx = idx;
        }
    }

    return min_vertex_idx;
}

std::vector<int> dijkstra_algorithm(const std::vector<std::vector<std::pair<int,int>>>& graph, int vertex)
{
    if (vertex >= graph.size())
        throw std::invalid_argument("incorrect vertex");

    std::vector<int> min_distances(graph.size(), std::numeric_limits<int>::max());
    min_distances[vertex] = 0;

    std::unordered_set<int> visited;
    while (visited.size() < graph.size()) {
        const auto current_vertex_idx = find_vertex_with_min_distance(min_distances, visited);
        visited.insert(current_vertex_idx);

        for (const auto& edge: graph[current_vertex_idx]) {
            const auto vertex_id = edge.first;
            const auto vertex_distance = edge.second + min_distances[current_vertex_idx];
            if (vertex_distance < min_distances[vertex_id])
                min_distances[vertex_id] = vertex_distance;
        }
    }

    return min_distances;
}

int main(int argc, char** argv)
{
    std::vector<std::vector<std::pair<int, int>>> graph{
            {{2,1}, {1,4}},
            {{0,4}, {3,3}},
            {{0,1}, {3,2}},
            {{1,3},{2,2}},
    };

    const auto result = dijkstra_algorithm(graph, 0);
    for (const auto distance: result)
        std::cout << distance << std::endl;

    return EXIT_SUCCESS;
}