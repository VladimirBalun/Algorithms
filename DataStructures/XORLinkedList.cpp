#include <iostream>
#include <cinttypes>

template<typename T>
class XORLinkedList
{
public:
    struct Node
    {
        T value;
        Node* link;
    };

    void pushBack(const T& value)
    {
        Node* new_node = new Node{ value, nullptr };
        new_node->link = XOR(new_node, m_tail);
        m_tail = new_node;
    }

    template<typename U>
    void forEach(U func) const noexcept
    {
        Node* iterator = m_tail;
        while (iterator) {
            try {
                func(iterator);
            } catch (...) {}
            iterator = XOR(iterator, iterator->link);
        }
    }

    ~XORLinkedList()
    {
        Node *iterator = m_tail;
        while (iterator) {
            Node* temp = iterator;
            iterator = XOR(iterator, iterator->link);
            delete temp;
        }
    }
private:
    Node* XOR(const Node* lhs, const Node* rhs) const noexcept
    {
        return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(lhs) ^ reinterpret_cast<uintptr_t>(rhs));
    }
private:
    Node* m_tail = nullptr;
};

int main(int argc, char** argv)
{
    XORLinkedList<int> list;
    list.pushBack(1000);
    list.pushBack(2000);
    list.pushBack(3000);

    list.forEach([](auto it) {
        std::cout << it->value << std::endl;
    });

    return EXIT_SUCCESS;
}
