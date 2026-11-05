#include <iostream>
#include <vector>
#include <string>

using namespace std;

void increment(int& num);

int main()
{
    int a = 0;
    
    for (int i = 0; i < 10; i++) {
        increment(a);
    }
    std::cout << a << std::endl;
}

void increment(int& num) {
    num += 1;
}



