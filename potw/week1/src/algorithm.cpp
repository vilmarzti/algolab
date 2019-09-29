#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

void testcase(){
    int num, goal;
    std::cin >> num >> goal;

    // Read the vector
    std::vector<int> vec;
    for(int n=0; n<num; n++){
        int x;
        std::cin >> x;
        vec.push_back(x);
    }

    // implement sliding window
    int i=0, j=1, sum=vec.at(0);
    int best_i=0, best_j=0, best_sum=INT32_MAX;
    volatile int val, best_val;
    while((i<=j) && (j < num)){

        // check if results is correct or whether we need
        // to increase the left or right hand side
        if(sum == goal){
            std::cout << i << " " << j - 1 << std::endl;
            return;
        } else if(sum < goal){
            sum += vec.at(j);
            j++;
        } else if (sum > goal){
            sum -= vec.at(i);
            i++;
        }

        val = abs(sum - goal);
        best_val = abs(best_sum - goal);
        if (val < best_val){
            best_sum = sum;
            best_i = i;
            best_j = j - 1;
        }

    }

    std::cout  << best_i << " " << best_j << std::endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for(int n=0; n<t;n++){
        testcase();

    }
}
