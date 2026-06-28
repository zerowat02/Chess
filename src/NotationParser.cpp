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
    if(move.length() == 4){
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
    return (col-'a')*2+2;
}

pair<GridPos, GridPos> NotationParser::UCItoGrid(std::string move)
{

    GridPos src = {toCellCol(move[0]),toCellRow(move[1])};
    GridPos dest = {toCellCol(move[2]),toCellRow(move[3])};
    
    return {src, dest};

}

bool NotationParser::isCastling(std::string move)
{
    return (move == WHITE_LONG_CASTLE || move == WHITE_SHORT_CASTLE || move == BLACK_LONG_CASTLE || move == BLACK_SHORT_CASTLE);
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
