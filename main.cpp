#include "meta_ttt.h"
#include <iostream>

int main()
{
    typedef Board<O, X, O,
                  X, O, E,
                  X, E, O> B;

    std::cout << B::OWin << std::endl;
    std::cout << B::XWin << std::endl;

    return 0;
}
