#include "meta_ttt.h"
#include <iostream>

int main()
{
    typedef Board<O, E, E,
                  X, O, E,
                  X, E, E> B;

    std::cout << B::EvalOnly<O> << std::endl;
    std::cout << B::EvalOnly<X> << std::endl;
    std::cout << B::Score<O> << std::endl;
    std::cout << B::Score<X> << std::endl;

    return 0;
}
