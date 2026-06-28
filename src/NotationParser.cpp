#include "NotationParser.h"


bool NotationParser::isValidRow(char row)
{
    Logger::debug("NotationParser", "Checking if %c is valid Row", row);
    return row>='a' && row<='h';
}

bool NotationParser::isValidColum(char col)
{
    Logger::debug("NotationParser", "Checking if %c is valid Col", col);
    return col>='1' && col<='8';
}

bool NotationParser::isValidUCINotation(std::string move)
{
    if(move.length() == 4){
        return isValidRow(move[0]) && isValidColum(move[1]) && isValidRow(move[2]) && isValidColum(move[3]);
    }
    return false;
}

int NotationParser::toCellRow(char row)
{
    return (row-'a')*2;
}

int NotationParser::toCellCol(char col)
{
    return (col-'1')*2+2;
}

std::pair<GridPos, GridPos> NotationParser::UCItoGrid(std::string move)
{

    GridPos src = {toCellRow(move[0]),toCellCol(move[1])};
    GridPos dest = {toCellRow(move[2]),toCellCol(move[3])};
    
    return {src, dest};

}


