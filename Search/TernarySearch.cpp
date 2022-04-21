#include <vector>
#include <cassert>
#include <iostream>

int ternary_search_max(const std::vector<int>& data)
{
    if (data.empty())
        return -1;

    int left = 0;
    int right = data.size() - 1u;
    while (left != right) {
        const int m1 = left + (right - left) / 3;
        const int m2 = right - (right - left) / 3;
        if (data[m2] > data[m1])
            left = m1 + 1;
        else
            right = m2 - 1;
    }

    return left;
}

int main(int argc, char** argv)
{
    assert(ternary_search_max((std::vector<int>{ 1,3,1 })) == 1);
    assert(ternary_search_max((std::vector<int>{ 1,2,3,2,1 })) == 2);
    assert(ternary_search_max((std::vector<int>{ 1,2,3,5,3,2,1 })) == 3);
    assert(ternary_search_max((std::vector<int>{ 1,9,5,4,3,2,1 })) == 1);
    assert(ternary_search_max((std::vector<int>{ 1,2,3,4,5,9,1 })) == 5);
    assert(ternary_search_max((std::vector<int>{ 1,2,9,5,4,3,2 })) == 2);
    assert(ternary_search_max((std::vector<int>{ 1,2,3,4,9,2,1 })) == 4);
    return EXIT_SUCCESS;
}
