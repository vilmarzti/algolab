#include <iostream>
#include <vector>
#include <cmath>

void testcase(int y){
    long n;
    long k; 
    std::cin >> n >> k;

    int v;
    std::vector<long> vec;
    for(int m=0; m<n; m++){
        std::cin >> v;
        vec.push_back(v);
    }

    std::vector<long> sum;
    for(int x=0; x<n; x++){
        if(x == 0){
            sum.push_back(vec.at(0));
        }else{
            sum.push_back(sum.at(x-1) + vec.at(x));
        }
    }

    bool found = false;
    long sol_i, sol_j, val_i, val_j;
    long partialSum;
    long val = -1;
    for(long i=0; i<n; i++){
        for(long j=i; j<n; j++){
            if(i == 0){
                partialSum = sum.at(j);
            }
            else{
                partialSum = sum.at(j) - sum.at(i - 1);
            }
            if(val == -1 || std::abs(val-k) > std::abs(partialSum - k)){
                val = partialSum;
                val_i = i;
                val_j = j;
            }


            if(partialSum > k){
                break;
            }

            if(partialSum == k){
                found = true;
                sol_i = i  ;
                sol_j = j;
                break;
            }

        }
        if(found){
            break;
        }
    }

    if (found){
        std::cout << sol_i << " " << sol_j << std::endl;
    }else{
        std::cout << val_i << " " << val_j << std::endl;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for(int n=0; n<t; n++){
        testcase(n);
    }
}