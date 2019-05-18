#include <algorithm>

// These are the values each location can have.
enum Piece { O, X, E };

// Define the possible results of the game.
enum Result { W = 1, D = 0, L = -1 };

// This class checks all 3-in-a-row possibilities for the piece type t.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9,
          Piece t>
class LineChecker
{
public:
    enum
    {
        Horiz = (p1 == t && p2 == t && p3 == t)
            || (p4 == t && p5 == t && p6 == t)
            || (p7 == t && p8 == t && p9 == t),

        Vert = (p1 == t && p4 == t && p7 == t)
            || (p2 == t && p5 == t && p8 == t)
            || (p3 == t && p6 == t && p9 == t),

        Diag = (p1 == t && p5 == t && p9 == t)
            || (p3 == t && p5 == t && p7 == t),

        Win = Horiz || Vert || Diag
    };
};

// Evaluate the position.
// This is only guaranteed to be accurate if the position is terminal - otherwise it will report draw.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9,
          Piece t>
class Eval
{
public:
    enum
    {
        Score = LineChecker<p1, p2, p3, p4, p5, p6, p7, p8, p9, t>::Win ? W
            : LineChecker<p1, p2, p3, p4, p5, p6, p7, p8, p9, t == O ? X : O>::Win ? L
            : D
    };
};

// This is a "min" node in the minimax tree.
// The piece type "m" is being minimised for.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9,
          Piece m>
class MinNode
{
public:
    enum
    {
        Full = p1 != E && p2 != E && p3 != E && p4 != E && p5 != E && p6 != E && p7 != E && p8 != E && p9 != E,
        M1 = p1 == E ? MaxNode<m, p2, p3, p4, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M2 = p1 == E ? MaxNode<p1, m, p3, p4, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M3 = p1 == E ? MaxNode<p1, p2, m, p4, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M4 = p1 == E ? MaxNode<p1, p2, p3, m, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M5 = p1 == E ? MaxNode<p1, p2, p3, p4, m, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M6 = p1 == E ? MaxNode<p1, p2, p3, p4, p5, m, p7, p8, p9, m == O ? X : O>::Score : L,
        M7 = p1 == E ? MaxNode<p1, p2, p3, p4, p5, p6, m, p8, p9, m == O ? X : O>::Score : L,
        M8 = p1 == E ? MaxNode<p1, p2, p3, p4, p5, p6, p7, m, p9, m == O ? X : O>::Score : L,
        M9 = p1 == E ? MaxNode<p1, p2, p3, p4, p5, p6, p7, p8, m, m == O ? X : O>::Score : L
    };

    typedef Eval<p1, p2, p3, p4, p5, p6, p7, p8, p9, m> Ev;

    static constexpr int ChildVals[] = { M1, M2, M3, M4, M5, M6, M7, M8, M9 };
    static constexpr int Score = (Full && Ev::Score == D) ? D
        : Ev::Score != D ? -Ev::Score
        : *std::min_element(std::begin(ChildVals), std::end(ChildVals));
};

// This is a "max" node in the minimax tree.
// The piece type "m" is being maximised for.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9,
          Piece m>
class MaxNode
{
public:
    enum
    {
        Full = p1 != E && p2 != E && p3 != E && p4 != E && p5 != E && p6 != E && p7 != E && p8 != E && p9 != E,
        M1 = p1 == E ? MinNode<m, p2, p3, p4, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M2 = p1 == E ? MinNode<p1, m, p3, p4, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M3 = p1 == E ? MinNode<p1, p2, m, p4, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M4 = p1 == E ? MinNode<p1, p2, p3, m, p5, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M5 = p1 == E ? MinNode<p1, p2, p3, p4, m, p6, p7, p8, p9, m == O ? X : O>::Score : L,
        M6 = p1 == E ? MinNode<p1, p2, p3, p4, p5, m, p7, p8, p9, m == O ? X : O>::Score : L,
        M7 = p1 == E ? MinNode<p1, p2, p3, p4, p5, p6, m, p8, p9, m == O ? X : O>::Score : L,
        M8 = p1 == E ? MinNode<p1, p2, p3, p4, p5, p6, p7, m, p9, m == O ? X : O>::Score : L,
        M9 = p1 == E ? MinNode<p1, p2, p3, p4, p5, p6, p7, p8, m, m == O ? X : O>::Score : L
    };

    typedef Eval<p1, p2, p3, p4, p5, p6, p7, p8, p9, m> Ev;

    static constexpr int ChildVals[] = { M1, M2, M3, M4, M5, M6, M7, M8, M9 };
    static constexpr int Score = (Full && Ev::Score == D) ? D
        : Ev::Score != D ? Ev::Score
        : *std::max_element(std::begin(ChildVals), std::end(ChildVals));
};

// This class stores the board state.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9>
class Board
{
public:
    enum
    {
        OWin = LineChecker<p1, p2, p3, p4, p5, p6, p7, p8, p9, O>::Win,
        XWin = LineChecker<p1, p2, p3, p4, p5, p6, p7, p8, p9, X>::Win,
        OEval = Eval<p1, p2, p3, p4, p5, p6, p7, p8, p9, O>::Score,
        XEval = Eval<p1, p2, p3, p4, p5, p6, p7, p8, p9, X>::Score
    };

    template <Piece p>
    constexpr int Score = MaxNode<p1, p2, p3, p4, p5, p6, p7, p8, p9, p>::Score;
};
