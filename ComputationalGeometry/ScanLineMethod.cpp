#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

enum class PointType 
{
    START_SEGMENT = 0,
    END_SEGMENT
};

template<typename T>
struct Point 
{
    T x = 0;
    T y = 0;
    PointType type = PointType::START_SEGMENT;

    bool operator < (const Point& other) noexcept 
    {
        return x < other.x;
    }
};

template<typename T>
struct Segment
{
    T start_x_point = 0;
    T end_x_point = 0;
};

template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
Segment<T> find_line_segment_covered_largest_number_segments(std::vector<Point<T>> segments_points) noexcept
{
    std::sort(segments_points.begin(), segments_points.end());

    std::size_t accumulator = 0;
    std::size_t max_count_segments = 0;
    Segment<T> largest_segment{};
    for (const auto& point : segments_points)
    {
        if (point.type == PointType::START_SEGMENT)
        {
            accumulator++;
            if (accumulator > max_count_segments) 
            {
                max_count_segments = accumulator;
                largest_segment.start_x_point = point.x;
            }
        }
        else if (point.type == PointType::END_SEGMENT)
        {
            accumulator--;
            if (accumulator == (max_count_segments - 1)) 
            {
                largest_segment.end_x_point = point.x;
            }
        }
    }

    return largest_segment;
}

int main()
{
    std::vector<Point<float>> segments_points = {
        { 1.0f, 3.0f, PointType::START_SEGMENT }, { 5.0f, 3.0f, PointType::END_SEGMENT },
        { 2.0f, 1.0f, PointType::START_SEGMENT }, { 4.0f, 1.0f, PointType::END_SEGMENT },
        { 3.0f, 4.0f, PointType::START_SEGMENT }, { 4.0f, 4.0f, PointType::END_SEGMENT },
        { 3.0f, 2.5f, PointType::START_SEGMENT }, { 7.0f, 2.5f, PointType::END_SEGMENT },
        { 4.5f, 1.0f, PointType::START_SEGMENT }, { 11.0f, 1.0f, PointType::END_SEGMENT },
        { 6.0f, 4.0f, PointType::START_SEGMENT }, { 11.0f, 4.0f, PointType::END_SEGMENT }
    };

    Segment<float> segment = find_line_segment_covered_largest_number_segments(segments_points);
    std::cout << "Largest segment: (" << segment.start_x_point << "; " << segment.end_x_point << ")" << std::endl;

    return EXIT_SUCCESS;
}
