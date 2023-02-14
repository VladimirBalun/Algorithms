#include <stack>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

std::vector<int> topological_sort(std::unordered_map<int, std::vector<int>>& graph)
{
    std::stack<int> stack;
    std::unordered_set<int> visited;

    std::function<void(int)> topological_sort_impl;
    topological_sort_impl = [&topological_sort_impl, &graph, &visited, &stack] (int from_vertex)
    {
        visited.insert(from_vertex);
        for (const auto to_vertex: graph[from_vertex]) {
            if (visited.count(to_vertex) == 0)
                topological_sort_impl(to_vertex);
        }

        stack.push(from_vertex);
    };

    for (const auto& it: graph) {
        const auto vertex = it.first;
        if (visited.count(vertex) == 0) {
            topological_sort_impl(vertex);
        }
    }

    std::vector<int> result;
    result.reserve(stack.size());
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }

    return result;
}

int main(int argc, char** argv)
{
    std::unordered_map<int, std::vector<int>> graph{
            {5, {2, 0}},
            {4, {0, 1}},
            {2, {3}},
            {3, {1}},
    };

    const auto result = topological_sort(graph);
    for (const auto vertex: result)
        std::cout << vertex << std::endl;

    return EXIT_SUCCESS;
}