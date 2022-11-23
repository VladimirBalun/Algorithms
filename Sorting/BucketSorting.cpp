#include <vector>
#include <iostream>

void bucket_sorting(std::vector<int>& data)
{
    if (data.size() < 2)
        return;

    auto min = std::numeric_limits<int>::max();
    auto max = std::numeric_limits<int>::min();
    for (const auto value: data) {
        min = std::min(min, value);
        max = std::max(max, value);
    }

    const auto range = max - min;
    const auto buckets_number = data.size() / 2;
    std::vector<std::vector<int>> buckets(buckets_number + 1);
    for (const auto value: data) {
        const auto index = value * buckets_number / range;
        buckets.at(index).push_back(value);
    }

    for (auto& bucket: buckets)
        std::sort(begin(bucket), end(bucket));

    size_t index = 0;
    for (const auto& bucket: buckets) {
        for (const auto value: bucket) {
            data[index++] = value;
        }
    }
}

int main()
{
    std::vector<int> vector = { 4, 7, 1, 5, 2, 9, 4, 7, 2, 9, 4 };

    std::cout << "Not sorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    bucket_sorting(vector);

    std::cout << "\nSorted array: ";
    for (const auto& value : vector)
        std::cout << value << " ";

    return EXIT_SUCCESS;
}