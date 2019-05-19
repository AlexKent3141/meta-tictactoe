#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../meta_ttt.h"

TEST_CASE("Horizontal wins are detected for O", "[Wins]")
{
    typedef Board<O, O, O,
                  X, E, X,
                  E, X, O> B;

    int valO = B::EvalOnly<O>;
    int valX = B::EvalOnly<X>;
    REQUIRE(valO == W);
    REQUIRE(valX == L);
}

TEST_CASE("Horizontal wins are detected for X", "[Wins]")
{
    typedef Board<E, O, O,
                  X, X, X,
                  E, X, O> B;

    int valO = B::EvalOnly<O>;
    int valX = B::EvalOnly<X>;
    REQUIRE(valO == L);
    REQUIRE(valX == X);
}

TEST_CASE("Vertical wins are detected for O", "[Wins]")
{
    typedef Board<E, X, O,
                  X, E, O,
                  E, X, O> B;

    int valO = B::EvalOnly<O>;
    int valX = B::EvalOnly<X>;
    REQUIRE(valO == W);
    REQUIRE(valX == L);
}

TEST_CASE("Vertical wins are detected for X", "[Wins]")
{
    typedef Board<X, O, O,
                  X, E, E,
                  X, X, O> B;

    int valO = B::EvalOnly<O>;
    int valX = B::EvalOnly<X>;
    REQUIRE(valO == L);
    REQUIRE(valX == W);
}

TEST_CASE("Diagonal wins are detected for O", "[Wins]")
{
    typedef Board<O, X, E,
                  X, O, E,
                  E, X, O> B;

    int valO = B::EvalOnly<O>;
    int valX = B::EvalOnly<X>;
    REQUIRE(valO == W);
    REQUIRE(valX == L);
}

TEST_CASE("Diagonal wins are detected for X", "[Wins]")
{
    typedef Board<E, O, X,
                  O, X, E,
                  X, X, O> B;

    int valO = B::EvalOnly<O>;
    int valX = B::EvalOnly<X>;
    REQUIRE(valO == L);
    REQUIRE(valX == W);
}
