#include <stack>
#include <vector>
#include <iostream>
#include <forward_list>

struct AdjacencyList
{
    using view_type = std::vector<std::vector<int>>;
};

struct AdjacencyMatrix
{
    using view_type = std::vector<std::vector<int>>;
};

template<typename T>
using GraphViewType = typename T::view_type;

namespace details
{

    template<typename T>
    std::forward_list<int> dfs_impl(int start_vertex, const GraphViewType<T>& graph_view);

    template<>
    inline std::forward_list<int> dfs_impl<AdjacencyList>(int start_vertex, const GraphViewType<AdjacencyList>& graph_view)
    {
        std::stack<int> stack_helper{};
        stack_helper.push(start_vertex);
        std::forward_list<int> result{};
        std::vector<bool> visited_vertices(graph_view.size());
        while (!stack_helper.empty())
        {
            const int current_vertex = stack_helper.top();
            stack_helper.pop();
            result.push_front(current_vertex);
            const std::vector<int>& row_vertices = graph_view.at(current_vertex);
            for (int vertex : row_vertices)
            {
                if (!visited_vertices.at(vertex))
                {
                    visited_vertices.at(vertex) = true;
                    stack_helper.push(vertex);
                }
            }
        }

        return result;
    }

    template<>
    inline std::forward_list<int> dfs_impl<AdjacencyMatrix>(int start_vertex, const GraphViewType<AdjacencyMatrix>& graph_view)
    {
        std::stack<int> stack_helper{};
        stack_helper.push(start_vertex);
        std::vector<bool> visited_vertices(graph_view.size());
        std::forward_list<int> result{};
        while (!stack_helper.empty())
        {
            const int current_vertex = stack_helper.top();
            stack_helper.pop();
            result.push_front(current_vertex);
            const std::vector<int>& row_vertices = graph_view.at(current_vertex);
            for (std::size_t i = 0u; i < row_vertices.size(); ++i)
            {
                const int suggested_vertex = row_vertices.at(i);
                if ( (suggested_vertex > 0) && (!visited_vertices.at(i)) )
                {
                    visited_vertices.at(i) = true;
                    stack_helper.push(i);
                }
            }
        }

        return result;
    }

}

template<typename T>
std::forward_list<int> dfs(int start_vertex, const GraphViewType<T>& graph_view)
{
    return details::dfs_impl<T>(start_vertex, graph_view);
}

int main()
{
    //          0          
    //         / \         
    //        1   2        
    //       / \   \       
    //      3---4   5      
    //               \     
    //                6    

    {
        GraphViewType<AdjacencyMatrix> adjacency_matrix = {
            { 0, 1, 1, 0, 0, 0, 0 },
            { 1, 0, 0, 1, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 1, 0, 0 },
            { 0, 1, 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 1 },
            { 0, 0, 0, 0, 0, 1, 0 }
        };

        std::cout << "DFS for adjacency matrix: ";
        std::forward_list<int> result = dfs<AdjacencyMatrix>(0, adjacency_matrix);
        result.reverse();
        for (const int vertex : result)
        {
            std::cout << vertex << "   ";
        }
    }

    {
        GraphViewType<AdjacencyList> adjacency_list = {
            { 1, 2 },
            { 0, 3, 4 },
            { 0, 5 },
            { 1, 4 },
            { 1, 3 },
            { 2, 6 },
            { 5 }
        };

        std::cout << "\nDFS for adjacency list: ";
        std::forward_list<int> result = dfs<AdjacencyList>(0, adjacency_list);
        result.reverse();
        for (const int vertex : result)
        {
            std::cout << vertex << "   ";
        }
    }

    return EXIT_SUCCESS;
}
