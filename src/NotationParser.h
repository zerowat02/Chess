#pragma once
#include<CoordinateTypes.h>
#include<vector>
#include <string>
#include<Logger.h>
#include<Piece.h>
using namespace std;

static const std::string WHITE_SHORT_CASTLE = "e1g1";
static const std::string WHITE_LONG_CASTLE  = "e1c1";
static const std::string BLACK_SHORT_CASTLE = "e8g8";
static const std::string BLACK_LONG_CASTLE  = "e8c8";
static const char QUEEN  = 'q';
static const char ROOK  = 'r';
static const char BISHOP  = 'b';
static const char KNIGHT  = 'n';

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
    static GridPos halfUCItoGrid(std::string move);    
    static bool isCastling(std::string move, PieceType pieceType);
    static bool isEnPassant(std::string move, PieceType pieceType);
    static bool isPromotion(std::string move);
    static std::string getTowerCastlingMoves(std::string move);
    static PieceType getPromotionPiece(std::string move);

}; 

