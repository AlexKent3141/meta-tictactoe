#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../meta_ttt.h"

TEST_CASE("Horizontal wins are detected for O", "[Wins]")
{
    typedef Board<O, O, O,
                  X, E, X,
                  E, X, O> BO;

    REQUIRE(BO::OWin);
    REQUIRE(!BO::XWin);
}

TEST_CASE("Horizontal wins are detected for X", "[Wins]")
{
    typedef Board<E, O, O,
                  X, X, X,
                  E, X, O> BX;

    REQUIRE(BX::XWin);
    REQUIRE(!BX::OWin);
}

TEST_CASE("Vetical wins are detected for O", "[Wins]")
{
    typedef Board<E, X, O,
                  X, E, O,
                  E, X, O> BO;

    REQUIRE(BO::OWin);
    REQUIRE(!BO::XWin);
}

TEST_CASE("Vertical wins are detected for X", "[Wins]")
{
    typedef Board<X, O, O,
                  X, E, E,
                  X, X, O> BX;

    REQUIRE(BX::XWin);
    REQUIRE(!BX::OWin);
}

TEST_CASE("Diagonal wins are detected for O", "[Wins]")
{
    typedef Board<O, X, E,
                  X, O, E,
                  E, X, O> BO;

    REQUIRE(BO::OWin);
    REQUIRE(!BO::XWin);
}

TEST_CASE("Diagonal wins are detected for X", "[Wins]")
{
    typedef Board<E, O, X,
                  O, X, E,
                  X, X, O> BX;

    REQUIRE(BX::XWin);
    REQUIRE(!BX::OWin);
}
