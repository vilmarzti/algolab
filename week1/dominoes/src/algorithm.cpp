#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

void testcase(){
    std::vector<int> vec;
    int n;
    std::cin >> n;
    for(int x=0; x<n;x++){
        int m;
        std::cin >> m;
        vec.push_back(m);
    }

    unsigned int idx=0;
    unsigned int distance = 1;
    while(distance > 0 && idx<n){
        unsigned int x = vec.at(idx);

        if(distance < x){
            distance = x ;
        }

        if(distance > n){
            idx = n;
            break;
        }

        idx += 1;
        distance -= 1;
    }
    std::cout << idx << std::endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for(int n=0;n<t; n++){
        testcase();
    }
}
