#include <vector>
#include <iostream>
#include <cmath>

template<
    typename Type,
    typename Function
>
class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<Type>& numbers)
        : m_tree(build_tree(numbers)), numbers_size(numbers.size()) {}

    [[nodiscard]] Type query(size_t left, size_t right) const noexcept
    {
        if (left < 1 || left > right || right > numbers_size)
            return Type{};

        left += numbers_size - 1;
        right += numbers_size - 1;

        Type result{};
        while (left <= right) {
            if (left % 2 != 0)
                result = Function()(result, m_tree[left]);
            if (right % 2 == 0)
                result = Function()(result, m_tree[right]);

            left = parent(left + 1);
            right = parent(right - 1);
        }

        return result;
    }

    void update(size_t index, Type value) noexcept
    {
        if (index < 1 || index > numbers_size)
            return;

        index += numbers_size - 1;
        m_tree[index] = value;

        do {
            index = parent(index);
            const auto left_child_idx = left_child(index);
            const auto right_child_idx = right_child(index);
            m_tree[index] = Function()(m_tree[left_child_idx], m_tree[right_child_idx]);
        } while (index > 1);
    }

private:
    static std::vector<Type> build_tree(const std::vector<Type>& numbers)
    {
        if (numbers.empty())
            throw std::invalid_argument("numbers are empty");

        const auto numbers_size = numbers.size();
        const auto size =  1 << static_cast<int>(std::log2(numbers_size - 1) + 1);

        std::vector<int> tree(size * 2);
        std::copy(begin(numbers), end(numbers), begin(tree) + size);

        for (size_t start_idx = size - 1; start_idx > 0; --start_idx) {
            const auto left_child_idx = left_child(start_idx);
            const auto right_child_idx = right_child(start_idx);
            tree[start_idx] = Function()(tree[left_child_idx], tree[right_child_idx]);
        }

        return tree;
    }

    [[nodiscard]] static size_t left_child(size_t index) noexcept
    {
        return index * 2;
    }

    [[nodiscard]] static size_t right_child(size_t index) noexcept
    {
        return index * 2 + 1;
    }

    [[nodiscard]] static size_t parent(size_t index) noexcept
    {
        return index / 2;
    }

private:
    std::vector<int> m_tree;
    const size_t numbers_size;
};

int main(int argc, char** argv)
{
    SegmentTree<int, std::plus<>> tree(std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
    std::cout << tree.query(1, 5) << std::endl;
    tree.update(1, 5);

    return EXIT_SUCCESS;
}