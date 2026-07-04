#include "Board.h"

bool Board::isAdiacientToOtherPiece(GridPos pos)
{
    for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                GridPos checking = {pos.first-i,pos.second+j};
                if(checking!=pos && isValid(checking)){
                    if(isOccupied(checking)){
                        return true;
                    }
                }
            }
        }    
    return false;
}

bool Board::isOccupied(GridPos pos)
{
    return false; // stub
}

Piece Board::getPiece(GridPos pos)
{
    return grid[pos.first][pos.second];
}

GridPos Board::nextFreeGraveyardSpot(PieceColor color)
{
    int startCol = (color == PieceColor::Black) ? 0 : GRAVEYARD_RIGHT_CELL_START;
    int endCol = (color == PieceColor::Black) ?  GRAVEYARD_LEFT_CELL_END: COL;
    GridPos cell;
    for(int col = startCol; col<endCol; col++){
        for(int row = 0; row<ROW; row++){
            cell = {row, col};
            if(isCell(cell) && !isOccupied(cell)){
                return cell;
            }
        }
    }
   
    // graveyard full
    return {-1,-1};
}

GridPos Board::getPiecePositioninGraveyard(Piece piece)
{
    int startCol = (piece.color == PieceColor::Black) ? 0 : GRAVEYARD_RIGHT_CELL_START;
    int endCol = (piece.color == PieceColor::Black) ?  GRAVEYARD_LEFT_CELL_END: COL;
    GridPos cell;
    for(int col = startCol; col<endCol; col++){
        for(int row = 0; row<ROW; row++){
            cell = {row, col};
            if(piece == grid[row][col]){
                return cell;
            }
        }
    }
   
    // graveyard full
    return {-1,-1};
}
