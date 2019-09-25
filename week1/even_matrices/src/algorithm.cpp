#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

void testcase(){
    int n;
    std::cin >> n;
    unsigned int matrix[n][n];
    for(int y=0; y<n; y++){
        for(int x=0; x<n; x++){
            int num;
            std::cin >> num;
            matrix[y][x] = num;
        }
    }

    std::cout << n << std::flush;
    unsigned int pSum[n][n];
    for(int y=0; y<n;y++){
        for(int x=0; x<n; x++){
            if (x == 0 && y == 0){
                pSum[0][0] = matrix[0][0];
            }
            else if(x == 0){
                pSum[y][x] = pSum[y-1][x] + matrix[y][x];
            }
            else if(y==0){
                pSum[y][x] = pSum[y][x-1] + matrix[y][x];
            }
            else{
                pSum[y][x] = pSum[y][x-1] + pSum[y-1][x] - pSum[y-1][x-1] + matrix[y][x];
            }
        }
    }


}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for(int x=0; x<t; x++){
        testcase();
    }
}
