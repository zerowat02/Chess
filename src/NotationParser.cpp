#include "NotationParser.h"


bool NotationParser::isValidRow(char row)
{
    Logger::debug("NotationParser", "Checking if %c is valid Row", row);
    return row>='1' && row<='8';
}

bool NotationParser::isValidColum(char col)
{
    Logger::debug("NotationParser", "Checking if %c is valid Col", col);
    return col>='a' && col<='h';
}

bool NotationParser::isValidUCINotation(std::string move)
{
    if(move.length() == 4 || isPromotion(move)){
        return isValidColum(move[0]) && isValidRow(move[1]) && isValidColum(move[2]) && isValidRow(move[3]);
    }
    return false;
}

int NotationParser::toCellRow(char row)
{
    return (row-'1')*2;
}

int NotationParser::toCellCol(char col)
{
    return (col-'a')*2+4;
}

pair<GridPos, GridPos> NotationParser::UCItoGrid(std::string move)
{

    GridPos src  = { toCellRow(move[1]), toCellCol(move[0]) };
    GridPos dest = { toCellRow(move[3]), toCellCol(move[2]) };
    
    return {src, dest};
}

GridPos NotationParser::halfUCItoGrid(std::string move)
{
    if(move.length() == 2 && isValidRow(move[1]) && isValidColum(move[0])){
        return GridPos { toCellRow(move[1]), toCellCol(move[0]) };
    }
    return GridPos{-1,-1};
}

bool NotationParser::isCastling(std::string move, PieceType pieceType)
{
    return pieceType == PieceType::King && (move == WHITE_LONG_CASTLE || move == WHITE_SHORT_CASTLE || move == BLACK_LONG_CASTLE || move == BLACK_SHORT_CASTLE);
}

bool NotationParser::isEnPassant(std::string move, PieceType pieceType)
{
    return pieceType == PieceType::Pawn && move[0]!=move[2];
}

bool NotationParser::isPromotion(std::string move)
{

    if (move.length() == 5){
        return move[4] == QUEEN ||  move[4] == ROOK ||  move[4] == BISHOP ||  move[4] == KNIGHT;
    }
    return false;
}

std::string NotationParser::getTowerCastlingMoves(std::string move)
{

    std::string whiteShortCastle = "h1f1";
    std::string whiteLongCastle = "a1d1";
    std::string blackShortCastle = "h8f8";
    std::string blackLongCastle = "a8d8";
    pair<GridPos, GridPos> kingMove;
    pair<GridPos, GridPos> towerMove;
    
    if(move == WHITE_SHORT_CASTLE){
        return(whiteShortCastle);
    }
    else if(move == WHITE_LONG_CASTLE){
        return(whiteLongCastle);
    }
    else if(move == BLACK_SHORT_CASTLE){
        return(blackShortCastle);
    }
    else if(move == BLACK_LONG_CASTLE){
        return(blackLongCastle);
    }
    
    Logger::debug("NotationParser", "%s is not a castling move", move.c_str());
    return {};


}

PieceType NotationParser::getPromotionPiece(std::string move)
{

    if (move.length() == 5){
        switch(move[4]) {
            case QUEEN:
                return PieceType::Queen;
                break;
            case ROOK:
                return PieceType::Rook;
                break;
            case BISHOP:
                return PieceType::Bishop;
                break;
            case KNIGHT:
                return PieceType::Knight;
                break;            
        }
    }
    Logger::error("NotationParser", "%s is not a valid promotion", move.c_str());
    return {};
}
