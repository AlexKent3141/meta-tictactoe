#include <algorithm>

// These are the values each location can have.
enum Piece { O, X, E };

// Define the possible results of the game.
enum Value { W = 1, D = 0, L = -1 };

// This class checks all 3-in-a-row possibilities for the piece type t.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9,
          Piece t>
struct LineChecker
{
    static constexpr bool Horiz = (p1 == t && p2 == t && p3 == t)
        || (p4 == t && p5 == t && p6 == t)
        || (p7 == t && p8 == t && p9 == t);

    static constexpr bool Vert = (p1 == t && p4 == t && p7 == t)
        || (p2 == t && p5 == t && p8 == t)
        || (p3 == t && p6 == t && p9 == t);

    static constexpr bool Diag = (p1 == t && p5 == t && p9 == t)
        || (p3 == t && p5 == t && p7 == t);

    static constexpr bool Win = Horiz || Vert || Diag;
};

// Evaluate the position.
// This is only guaranteed to be accurate if the position is terminal, otherwise it will report draw.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9,
          Piece t>
struct Eval
{
    static constexpr int Score = LineChecker<p1, p2, p3, p4, p5, p6, p7, p8, p9, t>::Win ? W
        : LineChecker<p1, p2, p3, p4, p5, p6, p7, p8, p9, t == O ? X : O>::Win ? L
        : D;
};

// Wrap up a result.
template<int res>
struct Result
{
    static constexpr int Score = res;
};

// Reaching an illegal board state counts as a loss.
typedef Result<L> Illegal;

// This class represents a node in the minimax tree.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9,
          Piece p>
struct Node
{
    typedef Eval<p1, p2, p3, p4, p5, p6, p7, p8, p9, p> Ev;

    static constexpr Piece q = p == O ? X : O;
    static constexpr int Full = p1 != E && p2 != E && p3 != E && p4 != E && p5 != E && p6 != E && p7 != E && p8 != E && p9 != E;
    static constexpr bool GameOver = Full || Ev::Score != D;

    // Search each child node.
    // Need to check that the game is not already over and that the point is not already occupied.
    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p1 == E, Node<p, p2, p3, p4, p5, p6, p7, p8, p9, q>,
            Illegal>> M1;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p2 == E, Node<p1, p, p3, p4, p5, p6, p7, p8, p9, q>,
            Illegal>> M2;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p3 == E, Node<p1, p2, p, p4, p5, p6, p7, p8, p9, q>,
            Illegal>> M3;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p4 == E, Node<p1, p2, p3, p, p5, p6, p7, p8, p9, q>,
            Illegal>> M4;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p5 == E, Node<p1, p2, p3, p4, p, p6, p7, p8, p9, q>,
            Illegal>> M5;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p6 == E, Node<p1, p2, p3, p4, p5, p, p7, p8, p9, q>,
            Illegal>> M6;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p7 == E, Node<p1, p2, p3, p4, p5, p6, p, p8, p9, q>,
            Illegal>> M7;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p8 == E, Node<p1, p2, p3, p4, p5, p6, p7, p, p9, q>,
            Illegal>> M8;

    typedef std::conditional_t<GameOver, Result<Ev::Score>,
            std::conditional_t<p9 == E, Node<p1, p2, p3, p4, p5, p6, p7, p8, p, q>,
            Illegal>> M9;

    static constexpr int ChildVals[] = { M1::Score, M2::Score, M3::Score, M4::Score, M5::Score, M6::Score, M7::Score, M8::Score, M9::Score };

    static constexpr int Score = GameOver ? -Ev::Score
        : -*std::max_element(std::begin(ChildVals), std::end(ChildVals));
};

// This class stores the board state.
template <Piece p1, Piece p2, Piece p3,
          Piece p4, Piece p5, Piece p6,
          Piece p7, Piece p8, Piece p9>
struct Board
{
    // Get the evaluation of this board state without searching.
    template <Piece p>
    static constexpr int EvalOnly = Eval<p1, p2, p3, p4, p5, p6, p7, p8, p9, p>::Score; 

    // Get the evaluation of this board state with search.
    template <Piece p>
    static constexpr int Score = -Node<p1, p2, p3, p4, p5, p6, p7, p8, p9, p>::Score;
};
