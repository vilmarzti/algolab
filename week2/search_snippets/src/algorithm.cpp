#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <tuple>
#include <stdexcept>

using namespace std;

void testcase(){
    size_t n;
    int max_m = 0;
    
    std::cin >> n;
    // read all the ms
    std::vector<int> m_vec;
    for(size_t x=0; x<n;x++){
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
    /*
    for(auto &tup: old_ranges){
        std::cout << "( " << std::get<0>(tup) << ", " << std::get<1>(tup) << ") ";
    }
    std::cout << std::endl;
    */
    for(size_t i=1; i<n; i++){
        std::vector<std::tuple<size_t, size_t>> new_ranges;
        std::vector<size_t> current_idx = p_matrix.at(i);

        size_t tup_index = 0;
        size_t p_index = 0;
        while(p_index < current_idx.size()){
            bool is_processed = false;
            volatile size_t p = current_idx.at(p_index);

            // the next p
            volatile size_t p_next = (p_index == current_idx.size() - 1) ? INT32_MAX : current_idx.at(p_index + 1);

            // the p that was before
            volatile size_t p_before = (p_index == 0) ? 0: current_idx.at(p_index - 1);

            // the lower bound from the tuple before
            volatile size_t lower = (tup_index == 0) ? 0 : std::get<1>(old_ranges.at(tup_index - 1));

            // the upper bound from the next tuple
            volatile size_t upper = (tup_index == old_ranges.size()) ? INT32_MAX : std::get<0>(old_ranges.at(tup_index));


            if( lower <= p && p <= upper){
                if(p_before <= lower){
                    new_ranges.push_back(make_tuple(lower, p));
                }
                if(p_next >= upper && tup_index < old_ranges.size()){
                    new_ranges.push_back(make_tuple(p, upper));
                }
                is_processed = true;
            }

            while(p>upper){
                volatile size_t first = std::get<0>(old_ranges.at(tup_index));
                volatile size_t second = std::get<1>(old_ranges.at(tup_index));
                if(first <= p && p <= second){
                    new_ranges.push_back(make_tuple(first, second));
                    is_processed = true;
                    break;
                }
                tup_index++;
                upper = (tup_index >= old_ranges.size() - 1) ? INT32_MAX : std::get<0>(old_ranges.at(tup_index));
            }
            if(is_processed){
                p_index++;
            }
        }
        old_ranges = new_ranges;
        /*        
        for(auto &tup: old_ranges){
            std::cout << "( " << std::get<0>(tup) << ", " << std::get<1>(tup) << ") ";
        }
        std::cout << std::endl;
        */
    }


    size_t min_range = INT32_MAX;
    for(size_t i=0; i< old_ranges.size(); i++){
        size_t first = std::get<0>(old_ranges.at(i));
        size_t second = std::get<1>(old_ranges.at(i));
        size_t diff = second - first;
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
