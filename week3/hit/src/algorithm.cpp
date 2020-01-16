#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 Point;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Segment;

void testcase(int n)
{
    long x, y, a, b;
    std::cin >> x >> y >> a >> b;
    Point p(x, y);
    Point q(a, b);
    Ray ray(p, q);

    long r, s, t, u;
    bool do_intersect = false;
    for (int i = 0; i < n; i++)
    {
        std::cin >> r >> s >> t >> u;
        if (!do_intersect)
        {
            Point v(r, s);
            Point w(t, u);
            Segment segment = Segment(v, w);
            if (CGAL::do_intersect(ray, segment))
            {
                do_intersect = true;
            }
        }
    }
    if (do_intersect)
    {
        std::cout << "yes\n";
    }
    else
    {
        std::cout << "no\n";
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    size_t n;
    std::cin >> n;

    while (n != 0)
    {
        testcase(n);
        std::cin >> n;
    }
}
