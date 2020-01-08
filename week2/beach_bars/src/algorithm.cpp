#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <tuple>
#include <stdexcept>
#include <math.h>

using namespace std;

void testcase()
{
    // read input
    std::vector<int> vec;
    size_t n;
    std::cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        size_t t;
        std::cin >> t;
        vec.push_back(t);
    }

    sort(vec.begin(), vec.end());
    
    // sliding window
    int i = 0;
    int j = 1;
    int val_i, val_j;
    int difference;
    int best_count = 0;
    int longest_distance = 0;
    float middle = 0;
    std::vector<float> best_pos;
    while (j < n && i < j)
    {
        val_i = vec.at(i);
        val_j = vec.at(j);
        difference = abs(val_j - val_i);

        if (j - i + 1 == best_count)
        {
            middle = (val_j + val_i) / 2.0;
            if (middle != floor(middle))
            {
                best_pos.push_back(floor(middle));
                best_pos.push_back(ceil(middle));
            }
            else
            {
                best_pos.push_back(middle);
            }
            longest_distance = max(abs(floor(middle) - val_i), abs(val_j - floor(middle)));
        }
        else if (j - i + 1 > best_count)
        {
            best_pos = {};
            middle = (val_j + val_i) / 2.0;
            if (middle != floor(middle))
            {
                best_pos.push_back(floor(middle));
                best_pos.push_back(ceil(middle));
            }
            else
            {
                best_pos.push_back(middle);
            }
            best_count = j - i + 1;
            longest_distance = max(abs(floor(middle) - val_i), abs(val_j - floor(middle)));
        }

        if (difference < 200)
        {
            j += 1;
        }
        else
        {
            i += 1;
        }
    }

    // print results
    std::cout << best_count << " " << longest_distance << "\n";
    for (int t = 0; t < best_pos.size(); t++)
    {
        std::cout << best_pos.at(t);
        if(t < best_pos.size() - 1){
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    size_t t;
    std::cin >> t;
    for (size_t i = 0; i < t; i++)
    {
        testcase();
    }
}
