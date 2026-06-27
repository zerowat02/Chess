
#include<CoordinateTypes.h>
#include<vector>
#include <string>
using namespace std;


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

}; 

