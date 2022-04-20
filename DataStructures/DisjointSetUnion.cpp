#include <cassert>
#include <iostream>
#include <unordered_map>

class DSU
{
    struct ElementData
    {
        int parent;
        int rank;
    };

public:
    void make_set(int value)
    {
        if (m_elements.count(value) == 0)
            m_elements.emplace(value, ElementData{ value, 1 });
    }

    void merge(int left, int right)
    {
        std::optional<int> left_parent = leader(left);
        if (!left_parent.has_value())
            return;

        std::optional<int> right_parent = leader(right);
        if (!right_parent.has_value())
            return;

        ElementData& left_parent_data = m_elements[*left_parent];
        ElementData& right_parent_data = m_elements[*right_parent];
        if (left_parent_data.rank < right_parent_data.rank) {
            m_elements[*left_parent].parent = *right_parent;
        } else if (left_parent_data.rank > right_parent_data.rank) {
            m_elements[*right_parent].parent = *left_parent;
        } else {
            m_elements[*left_parent].parent = *right_parent;
            ++m_elements[*right_parent].rank;
        }
    }

    std::optional<int> leader(int value)
    {
        const auto it = m_elements.find(value);
        if (it == end(m_elements))
            return std::nullopt;

        if (it->second.parent == value)
            return value;

        std::optional<int> result = leader(it->second.parent);
        if (!result.has_value())
            return std::nullopt;

        m_elements[value].parent = *result;
        return result;
    }

private:
    std::unordered_map<int, ElementData> m_elements;
};

int main(int argc, char** argv)
{
    DSU disjoint_set_union;
    disjoint_set_union.make_set(1);
    disjoint_set_union.make_set(2);
    disjoint_set_union.make_set(3);
    disjoint_set_union.make_set(4);
    disjoint_set_union.make_set(5);
    disjoint_set_union.make_set(6);
    disjoint_set_union.make_set(7);

    disjoint_set_union.merge(1, 2);

    disjoint_set_union.merge(3, 4);
    disjoint_set_union.merge(4, 5);
    disjoint_set_union.merge(5, 6);

    assert(disjoint_set_union.leader(0) == std::nullopt);
    assert(disjoint_set_union.leader(7) == std::optional<int>{ 7 });
    assert(disjoint_set_union.leader(1) == disjoint_set_union.leader(2));
    
    assert(disjoint_set_union.leader(3) == disjoint_set_union.leader(4));
    assert(disjoint_set_union.leader(4) == disjoint_set_union.leader(5));
    assert(disjoint_set_union.leader(5) == disjoint_set_union.leader(6));

    return EXIT_SUCCESS;
}
