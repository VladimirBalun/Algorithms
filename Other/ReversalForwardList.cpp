#include <iostream>
#include <forward_list>

template<typename T>
struct Node 
{
    Node(const T& data, std::shared_ptr<Node> next) noexcept :
        m_data(data), m_next(std::move(next)) {}

    T m_data{};
    std::shared_ptr<Node> m_next{};
};

template<typename T>
void reverse(std::shared_ptr<Node<T>>& root_node) noexcept
{
    std::shared_ptr<Node<T>> reversed_node{};
    while (root_node)
    {
        auto tmp_pointer = root_node->m_next;
        root_node->m_next = reversed_node;
        reversed_node = root_node;
        root_node = tmp_pointer;
    }
    root_node = reversed_node;
}

int main()
{
    auto root_node = std::make_shared<Node<int>>(1, 
        std::make_shared<Node<int>>(2, 
            std::make_shared<Node<int>>(3, 
                std::shared_ptr<Node<int>>{})));

    reverse(root_node);

    return EXIT_SUCCESS;
}