#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

void testcase(){
    // read input
    size_t n, m, k;
    std::cin >> n >> m >> k;
    
    //reads input vector
    std::vector<size_t> values;
    for (size_t i = 0; i < n; i++){
        size_t x;
        std::cin >> x;
        values.push_back(x);
    }
    
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    // TODO
    size_t t;
    std::cin >> t;
    for (size_t i = 0; i < t; i++)
    {
        testcase();
    }
}
