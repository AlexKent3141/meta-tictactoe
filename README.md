# meta-tictactoe
Solve tic-tac-toe at compile time using metaprogramming in C++. I've made extensive use of constexpr (C++11) and some C++14 language features to make something which is (hopefully) readable - for a metaprogram!

The Board class has 9 template arguments which represent the 9 locations on the tic-tac-toe board e.g.

```c++
typedef Board<O, E, E,
              X, O, E,
              X, E, E> B;
```

The board class exposes two methods:
* EvalOnly: Gets the evaluation (Win/Loss/Draw) of the current board state for the specified player.
* Score: Do a minimax search to determine the specified player's best result if they play next.

So given the above definition of "B" we can make the following calls:

```c++
std::cout << B::EvalOnly<O> << std::endl;
std::cout << B::EvalOnly<X> << std::endl;
std::cout << B::Score<O> << std::endl;
std::cout << B::Score<X> << std::endl;
```
the output is:

```
0 // The player "O" does not have 3-in-a-row
0 // The player "X" does not have 3-in-a-row
1 // The player "O" can win if they are next to play
0 // The best player "X" can do if they play first is draw
```

## Thoughts
This has been my first attempt at writing a C++ metaprogram and it has certainly highlighted a few learning points.
* Readability is very important and a lot harder to achieve than in "normal" C++.
* Debugging is a painful experience - trying to isolate bugs in the minimax routine using static assertions was very difficult. There must be a better way!
* Compilation time quickly becomes prohibitive. A program that solves the empty board state (and finds it to be a draw) takes around a minute to compile on my PC.

## TODO
* Try to make the code more readable - simplifying the nested conditionals would be good.
* Get the best move for the player along with their best result.
* Optimisations? It takes a while to compile if an empty board state is specified.
