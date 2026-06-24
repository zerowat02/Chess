#include "Robot.h"

void Robot::movePiece(GridPos src, GridPos dest)
{
    motion.fastMove(src);
    vector <GridPos> gridPath = planner.findPath(board, src, dest);
    if(gridPath.empty()){
        // probably will return error or something later on,or at least log it
        return;
    }
    for(GridPos cell : gridPath){
        if(board.isAdiacientToOtherPiece(cell)){
            //lower magnet power
        }
        else{
            //normal magnet power
        }
        motion.movePiece(kinematics.GridMoveToSteps(cell), Speed::MEDIUM);
    }
}