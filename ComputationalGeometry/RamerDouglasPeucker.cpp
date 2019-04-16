#include <vector>
#include <utility>
#include <iostream>
#include <type_traits>

#define X_COORDINATE 0
#define Y_COORDINATE 1

template<typename T>
using point_t = std::pair<T, T>;

template<typename T>
using line_segment_t = std::pair<point_t<T>, point_t<T>>;

template<typename T>
using points_t = std::vector<point_t<T>>;

template<typename CoordinateType>
double get_distance_between_point_and_line_segment(const line_segment_t<CoordinateType>& line_segment, const point_t<CoordinateType>& point) noexcept
{
    const CoordinateType x = std::get<X_COORDINATE>(point);
    const CoordinateType y = std::get<Y_COORDINATE>(point);

    const CoordinateType x1 = std::get<X_COORDINATE>(line_segment.first);
    const CoordinateType y1 = std::get<Y_COORDINATE>(line_segment.first);

    const CoordinateType x2 = std::get<X_COORDINATE>(line_segment.second);
    const CoordinateType y2 = std::get<Y_COORDINATE>(line_segment.second);

    const double double_area = abs((y2-y1)*x - (x2-x1)*y + x2*y1 - y2*x1);
    const double line_segment_length = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
    if (line_segment_length != 0.0)
        return double_area / line_segment_length;
    else
        return 0.0;
}

template<typename CoordinateType>
void simplify_points(const points_t<CoordinateType>& src_points, points_t<CoordinateType>& dest_points, double tolerance, std::size_t begin, std::size_t end)
{
    if (begin + 1 == end)
        return;

    double max_distance = -1.0;
    std::size_t max_index = 0;
    for (std::size_t i = begin + 1; i < end; i++)
    {
        const point_t<CoordinateType>& cur_point = src_points.at(i);
        const point_t<CoordinateType>& start_point = src_points.at(begin);
        const point_t<CoordinateType>& end_point = src_points.at(end);
        const double distance = get_distance_between_point_and_line_segment({ start_point, end_point }, cur_point);
        if (distance > max_distance)
        {
            max_distance = distance;
            max_index = i;
        }
    }

    if (max_distance > tolerance)
    {
        simplify_points(src_points, dest_points, tolerance, begin, max_index);
        dest_points.push_back(src_points.at(max_index));
        simplify_points(src_points, dest_points, tolerance, max_index, end);
    }
}

template<
    typename CoordinateType,
    typename = std::enable_if<std::is_integral<CoordinateType>::value || std::is_floating_point<CoordinateType>::value>::type>
points_t<CoordinateType> ramer_duglas_peucker(const points_t<CoordinateType>& src_points, double tolerance) noexcept
{
    if (tolerance <= 0)
        return src_points;

    points_t<CoordinateType> dest_points{};
    dest_points.push_back(src_points.front());
    simplify_points(src_points, dest_points, tolerance, 0, src_points.size() - 1);
    dest_points.push_back(src_points.back());
    return dest_points;
}

int main()
{
    points_t<int> source_points{ { 1, 5 }, { 2, 3 }, { 5, 1 }, { 6, 4 }, { 9, 6 }, { 11, 4 }, { 13, 3 }, { 14, 2 }, { 18, 5 } };
    points_t<int> simplify_points = ramer_duglas_peucker(source_points, 0.5);
    return EXIT_SUCCESS;
}