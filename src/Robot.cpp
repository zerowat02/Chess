#include "Robot.h"

MoveResult Robot::movePiece(GridPos src, GridPos dest)
{
       
    // if a piece is being eaten, then first the eaten piece needs to be moved twoards the side
    if(board.isOccupied(dest)){
        Logger::debug("Robot", "Eating piece in (%d,%d)", dest.first,dest.second);
        GridPos graveyardCell = board.nextFreeGraveyardSpot(board.getCell(dest).color);
        if(!board.isValid(graveyardCell)){
            return MoveResult::GraveyardFull;
        }
        movePiece(dest,graveyardCell);
    }

    if(src == dest)
        return MoveResult::OK;

    vector <GridPos> gridPath = planner.findPath(board, src, dest);

    if(gridPath.empty()){
        return MoveResult::PathFindingError;
    }

    Logger::debug("PathPlanner", "Moving under(%d,%d)", gridPath[0].first,gridPath[0].second);
    motion.fastMove(stepConverter.GridMoveToSteps(gridPath[0]));
    
    for(GridPos cell : gridPath){
        if(board.isAdiacientToOtherPiece(cell)){
            //lower magnet power
        }
        else{
            //normal magnet power
        }
        Logger::debug("PathPlanner", " moving to (%d,%d)", cell.first,cell.second);
        motion.movePiece(stepConverter.GridMoveToSteps(cell), Speed::MEDIUM);
    }

    return MoveResult::OK;
}

MoveResult Robot::movePiece(std::string UCImove)
{
    Logger::debug("Robot", "Handleing move %s", UCImove.c_str());
    if(!NotationParser::isValidUCINotation(UCImove)){
        Logger::debug("Robot", "%s not valid UCI notation", UCImove.c_str());
        return MoveResult::InvalidNotation;
    }
    std::pair<GridPos,GridPos> gridMove = NotationParser::UCItoGrid(UCImove);
    GridPos src = gridMove.first;
    GridPos dest = gridMove.second;
    Logger::debug("Robot", "%s => (%d,%d)->(%d,%d)", UCImove.c_str(),src.first,src.second,dest.first,dest.second);
    motion.enable();
    MoveResult result = movePiece(src, dest);
    motion.disable();
    return result;
}

void Robot::home()
{
    motion.home();
}
