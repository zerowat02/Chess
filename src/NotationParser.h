#pragma once
#include<CoordinateTypes.h>
#include<vector>
#include <string>
#include<Logger.h>
using namespace std;

const std::string WHITE_SHORT_CASTLE = "e1g1";
const std::string WHITE_LONG_CASTLE  = "e1c1";
const std::string BLACK_SHORT_CASTLE = "e8g8";
const std::string BLACK_LONG_CASTLE  = "e8c8";

class NotationParser
{
private:
    static bool isValidRow(char row);
    static bool isValidColum(char col);
    static int toCellRow(char row);
    static int toCellCol(char col);
public:

    static bool isValidUCINotation(std::string move);
    static std::pair<GridPos, GridPos>  UCItoGrid(std::string move);
    static bool isCastling(std::string move);
    static std::string getTowerCastlingMoves(std::string move);

}; 

