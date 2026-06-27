#include "NotationParser.h"


bool NotationParser::isValidRow(char row)
{
    return row>48 && row<57;
}

bool NotationParser::isValidColum(char col)
{
    return col>96 && col<105;
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
    return (row-49)*2;
}

int NotationParser::toCellCol(char col)
{
    return (col-96)*2;
}

std::pair<GridPos, GridPos> NotationParser::UCItoGrid(std::string move)
{

    GridPos src = {toCellRow(move[0]),toCellCol(move[1])};
    GridPos dest = {toCellRow(move[2]),toCellCol(move[3])};
    
    return {src, dest};
}


