#include<CoordinateTypes.h>

using namespace std;

enum class chessPiece { None, Pawn, Rook, Knight, Bishop, Queen, King };
enum class PieceColor { White, Black };


struct Cell{
    chessPiece piece;
    PieceColor color;
};

class Board{
    public:
        static constexpr int ROW = 8;
        static constexpr int COL = 10;
    private:
        Cell grid[ROW][COL];
    public:
        bool isAdiacientToOtherPiece(GridPos pos);
        bool isOccupied(GridPos pos);
        bool isValid(GridPos pos);
        Cell& getCell(GridPos pos);
};



