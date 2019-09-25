#include <iostream>

void testcase(){
    int n;
    std::cin >> n;
    int sum = 0;
    for(int m=0;m<n;m++){
        int x;
        std::cin >> x;
        sum += x;
    }
    std::cout << sum << std::endl;
}

int main(){
    int t;
    std::cin >> t;
    for(int n=0; n<t; n++){
        testcase();
    }
}