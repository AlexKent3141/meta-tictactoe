// These are the values each location can have.
enum Piece { O, X, E };

// This class checks all 3-in-a-row possibilities for the piece t.
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
        XWin = LineChecker<p1, p2, p3, p4, p5, p6, p7, p8, p9, X>::Win
    };
};
