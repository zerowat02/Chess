#include "Robot.h"

MoveResult Robot::movePiece(GridPos src, GridPos dest)
{
       
    // if a piece is being eaten, then first the eaten piece needs to be moved twoards the side
    if(board.isOccupied(dest)){
        GridPos graveyardCell = board.nextFreeGraveyardSpot(board.getCell(dest).color);
        if(!board.isValid(graveyardCell)){
            return MoveResult::GraveyardFull;
        }
        movePiece(dest,graveyardCell);
    }

    vector <GridPos> gridPath = planner.findPath(board, src, dest);
    
    if(gridPath.empty()){
        return MoveResult::PathFindingError;
    }

    motion.fastMove(gridPath[0]); // move under piece that is going to be moved 
    
    for(GridPos cell : gridPath){
        if(board.isAdiacientToOtherPiece(cell)){
            //lower magnet power
        }
        else{
            //normal magnet power
        }
        motion.movePiece(stepConverter.GridMoveToSteps(cell), Speed::MEDIUM);
    }

    return MoveResult::OK;
}

MoveResult Robot::movePiece(std::string UCImove)
{
    if(!NotationParser::isValidUCINotation(UCImove)){
        return MoveResult::InvalidNotation;
    }
    std::pair<GridPos,GridPos> gridMove = NotationParser::UCItoGrid(UCImove);
    GridPos src = gridMove.first;
    GridPos dest = gridMove.second;
    return movePiece(src,dest);
}

