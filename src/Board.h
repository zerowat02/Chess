#pragma once
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
        static constexpr int ROW = 15;
        static constexpr int COL = 23;
        static constexpr int GRAVEYARD_LEFT_CELL_END   = 3;   // rightmost left graveyard col
        static constexpr int GRAVEYARD_RIGHT_CELL_START = 19;  // leftmost right graveyard col
    private:
        Cell grid[ROW][COL];
    public:
        bool isAdiacientToOtherPiece(GridPos pos);
        bool isOccupied(GridPos pos);
        bool isValid(GridPos pos){
            return(pos.first<ROW && pos.second<COL && pos.first>=0 && pos.second>=0);
        }
        bool isCell(GridPos pos){
            return(isValid(pos) && pos.first%2 == 0 && pos.second%2 == 0);
        }
        Cell getCell(GridPos pos);
        GridPos nextFreeGraveyardSpot(PieceColor color);
};



