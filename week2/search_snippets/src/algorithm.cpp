#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <tuple>
#include <stdexcept>

using namespace std;

void testcase(){
    int n;
    int max_m = 0;
    
    std::cin >> n;
    // read all the ms
    std::vector<int> m_vec;
    for(int x; x<n;x++){
        int m;
        
        std::cin >> m;
        m_vec.push_back(m);
        if(m > max_m){
            max_m = m;
        }
    }

    // read n lines;
    std::vector<std::vector<size_t>> p_matrix;
    for (size_t i = 0; i < n; i++)
    {
        size_t p_size = m_vec.at(i);
        std::vector<size_t> p_vector;
        for (size_t k = 0; k < p_size; k++)
        {
            size_t p;
            std::cin >> p;
            p_vector.push_back(p);
        }
        
        p_matrix.push_back(p_vector);
    }
    
    // Algorithm

    //initialize the old_ranges
    std::vector<tuple<size_t, size_t>> old_ranges;
    for(size_t &i: p_matrix[0]) {
        old_ranges.push_back(make_tuple(i, i));
    }

    for(int i=0; i<n; i++){
        std::vector<std::tuple<size_t, size_t>> new_ranges;
        std::vector<size_t> current_idx = p_matrix.at(i);

        size_t tup_index = 0;
        size_t p_index = 0;
        bool first_time = true;

        while(p_index < current_idx.size()){
            size_t p = current_idx.at(p_index);
            size_t first = std::get<0>(old_ranges.at(tup_index));
            size_t second = std::get<1>(old_ranges.at(tup_index));

            if(p <= first){
                p_index++;
            } else if (first_time){
                volatile size_t before = current_idx.at(p_index - 1 );
                new_ranges.push_back(make_tuple(before, first));
                first_time = false;
            } else if (p > first){
                new_ranges.push_back(make_tuple(second, p));
                tup_index++;
            }

        }
       old_ranges = new_ranges;

        for(auto &tup: old_ranges){
            std::cout << "( " << std::get<0>(tup) << ", " << std::get<1>(tup) << ") ";
        }
        std::cout << std::endl;
    }


    int min_range = INT32_MAX;
    for(size_t i; i< old_ranges.size(); i++){
        int first = std::get<0>(old_ranges.at(i));
        int second = std::get<1>(old_ranges.at(i));
        int diff = second - first;
        min_range = (diff < min_range) ? diff : min_range;
 
    }
    std::cout << min_range + 1 << std::endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for(int n=0; n<t; n++){
        testcase();
    }
}
