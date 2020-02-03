#include <queue>
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
    std::forward_list<int> bfs_impl(int start_vertex, const GraphViewType<T>& graph_view);

    template<>
    inline std::forward_list<int> bfs_impl<AdjacencyList>(int start_vertex, const GraphViewType<AdjacencyList>& graph_view)
    {
        std::queue<int> queue_helper{};
        queue_helper.push(start_vertex);
        std::forward_list<int> result{};
        std::vector<bool> visited_vertices(graph_view.size());
        while (!queue_helper.empty())
        {
            const int current_vertex = queue_helper.front();
            queue_helper.pop();
            result.push_front(current_vertex);
            const std::vector<int>& row_vertices = graph_view.at(current_vertex);
            for (const int vertex : row_vertices)
            {
                if (!visited_vertices.at(vertex))
                {
                    visited_vertices.at(vertex) = true;
                    queue_helper.push(vertex);
                }
            }
        }

        return result;
    }

    template<>
    inline std::forward_list<int> bfs_impl<AdjacencyMatrix>(int start_vertex, const GraphViewType<AdjacencyMatrix>& graph_view)
    {
        std::queue<int> queue_helper{};
        queue_helper.push(start_vertex);
        std::vector<bool> visited_vertices(graph_view.size());
        std::forward_list<int> result{};
        while (!queue_helper.empty())
        {
            int current_vertex = queue_helper.front();
            queue_helper.pop();
            result.push_front(current_vertex);
            const std::vector<int>& row_vertices = graph_view.at(static_cast<std::size_t>(current_vertex));
            for (std::size_t i = 0u; i < row_vertices.size(); ++i) 
            {
                const int suggested_vertex = row_vertices.at(i);
                if ( (suggested_vertex > 0) && (!visited_vertices.at(i)) )
                {
                    visited_vertices.at(i) = true;
                    queue_helper.push(i);
                }
            }
        }

        return result;
    }

}

template<typename T>
std::forward_list<int> bfs(int start_vertex, const GraphViewType<T>& graph_view)
{
    return details::bfs_impl<T>(start_vertex, graph_view);
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

        std::cout << "BFS for adjacency matrix: ";
        std::forward_list<int> result = bfs<AdjacencyMatrix>(0, adjacency_matrix);
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

        std::cout << "\nBFS for adjacency list: ";
        std::forward_list<int> result = bfs<AdjacencyList>(0, adjacency_list);
        result.reverse();
        for (const int vertex : result)
        {
            std::cout << vertex << "   ";
        }
    }

    return EXIT_SUCCESS;
}
