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

TEST_CASE("Win in two moves for both players", "[Search]")
{
    typedef Board<E, O, E,
                  X, O, E,
                  E, X, E> B;

    int scoreO = B::Score<O>;
    int scoreX = B::Score<X>;
    REQUIRE(scoreO == W);
    REQUIRE(scoreX == W);
}

TEST_CASE("Win for O and loss for X", "[Search]")
{
    typedef Board<E, X, E,
                  E, O, E,
                  O, X, E> B;

    int scoreO = B::Score<O>;
    int scoreX = B::Score<X>;
    REQUIRE(scoreO == W);
    REQUIRE(scoreX == L);
}

TEST_CASE("Win for X and loss for O", "[Search]")
{
    typedef Board<E, O, E,
                  E, X, X,
                  E, O, E> B;

    int scoreO = B::Score<O>;
    int scoreX = B::Score<X>;
    REQUIRE(scoreO == L);
    REQUIRE(scoreX == W);
}

TEST_CASE("Three move win for O", "[Search]")
{
    typedef Board<E, E, E,
                  E, O, E,
                  E, X, E> B;

    int scoreO = B::Score<O>;
    int scoreX = B::Score<X>;
    REQUIRE(scoreO == W);
    REQUIRE(scoreX == D);
}
