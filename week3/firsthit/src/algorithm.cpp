#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <boost/optional/optional_io.hpp>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Segment;

double floor_to_double(const K::FT &x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

void testcase(int n)
{
    long x, y, a, b;
    std::cin >> x >> y >> a >> b;
    Point p(x, y);
    Point q(a, b);
    Ray ray(p, q);

    bool intersects = true;

    std::vector<Segment> segments(n);
    for (size_t i = 0; i < n; i++)
    {
        long r, s, u, v;
        std::cin >> r >> s >> u >> v;
        Point p1(r, s);
        Point p2(u, v);
        Segment seg = Segment(p1, p2);
        segments[i] = seg;
    }

    std::random_shuffle(segments.begin(), segments.end());

    bool isInside = false;
    Segment connection;
    for (size_t i = 0; i < n; i++)
    {
        Segment segment = segments[i];
        if (isInside ? CGAL::do_intersect(connection, segment) : CGAL::do_intersect(ray, segment))
        {
            auto intersection = CGAL::intersection(ray, segment);
            if (const Point *intpoint = boost::get<Point>(&*intersection))
            {
                connection = Segment(p, *intpoint);
                isInside = true;
            }
            else if (const Segment *intseg = boost::get<Segment>(&*intersection))
            {
                connection = Segment(p, intseg->start());
                if (CGAL::do_intersect(connection, intseg->end()))
                {
                    connection = Segment(p, intseg->end());
                }

                isInside = true;
            }
        }
    }

    if (isInside)
    {
        double x = floor_to_double(connection.end().x());
        double y = floor_to_double(connection.end().y());

        std::cout << fixed << setprecision(0) << x << " " << y << "\n";
    }
    else
    {
        std::cout << "no\n";
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    while (n != 0)
    {
        testcase(n);
        std::cin >> n;
    }
}