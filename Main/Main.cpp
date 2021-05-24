#include <iostream>
#include "TList.h"
int main()
{
    TList<int>c(10);
    for (int j = 0; j < 5; ++j) {
        c.InsLast(j);
    }
    TList<int> b = c.multiplesToK(2);
    for (auto& elem : b) {
        std::cout << elem << std::endl;
    }

    return 0;
}