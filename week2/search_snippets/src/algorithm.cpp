#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

void testcase(){
    int n;
    
    // read all the ms
    std::vector<int> m_vec;
    for(int x; x<n;x++){
        int m;
        std::cin >> m;
        m_vec.push_back(m);
    }

    // read n lines;
    std::vector<std::vector<int>> p_matrix;
    for (size_t i = 0; i < n; i++)
    {
        int p_size;
        std::vector<int> p_vector;
        p_size = m_vec.at(i);
        for (size_t i = 0; i < p_size; i++)
        {
            int p;
            std::cin >> p;
            p_vector.push_back(p);
        }
        
        p_matrix.push_back(p_vector);
    }

    // Algorithm
    //
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for(int n=0; n<t; n++){
        testcase();
    }
}
