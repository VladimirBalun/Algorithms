#include <stack>
#include <vector>
#include <iostream>
#include <forward_list>

struct AdjacencyMatrix
{
    using view_type = std::vector<std::vector<int> >;
};

namespace details
{

    template<typename GraphViewType>
    std::forward_list<int> dfs_impl(int start_vertex, const AdjacencyMatrix::view_type& graph_view);

    template<>
    inline std::forward_list<int> dfs_impl<AdjacencyMatrix>(int start_vertex, const typename AdjacencyMatrix::view_type& graph_view)
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
                if ((suggested_vertex > 0) && (!visited_vertices.at(i)))
                {
                    visited_vertices.at(i) = true;
                    stack_helper.push(i);
                }
            }
        }

        return result;
    }

}


template<typename GraphViewType>
std::forward_list<int> dfs(int start_vertex, const typename GraphViewType::view_type& graph_view)
{
    return details::dfs_impl<GraphViewType>(start_vertex, graph_view);
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

    AdjacencyMatrix::view_type adjacency_matrix = {
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

    return EXIT_SUCCESS;
}
