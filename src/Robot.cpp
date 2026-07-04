#include "Robot.h"

// if a piece is being eaten, then first the eaten piece needs to be moved twoards the graveyard
MoveResult Robot::movePieceToGraveyard(GridPos src)
{
    GridPos graveyardCell = board.nextFreeGraveyardSpot(board.getPiece(src).color);
        if(!board.isValid(graveyardCell)){
            return MoveResult::GraveyardFull;
        }
    return movePiece(src,graveyardCell);
}

MoveResult Robot::handleEnPassant(std::string UCImove)
{
    std::string halfUCIMove = {UCImove[2], UCImove[1]}; // extrapolating the position of pawn being eaten
    return movePieceToGraveyard(NotationParser::halfUCItoGrid(halfUCIMove));
}

MoveResult Robot::movePiece(GridPos src, GridPos dest)
{
    if(src == dest)
        return MoveResult::OK;

    vector <GridPos> gridPath = planner.findPath(board, src, dest);

    if(gridPath.empty()){
        return MoveResult::PathFindingError;
    }

    Logger::debug("PathPlanner", "Moving under(%d,%d)", gridPath[0].first,gridPath[0].second);

    motion.enable();
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
    motion.disable();
    return MoveResult::OK;
}

MoveResult Robot::handlePromotion(GridPos src,GridPos dest, Piece piece)
{
    // first move promotion piece form graveyard to board
    GridPos graveyard = board.getPiecePositioninGraveyard(piece);
    if(!board.isValid(graveyard)){
        Logger::error("Robot", "%s not found in graveyard for promotion", piece.toString().c_str());
        return MoveResult::PieceNotFound;
    }
    MoveResult result = movePiece(graveyard, dest);
    if (result != MoveResult::OK) return result;
    // move promoted pawn from board to graveyard
    return movePieceToGraveyard(src);
}

MoveResult Robot::movePiece(std::string UCImove)
{
    Logger::debug("Robot", "Handleing move %s", UCImove.c_str());

    // checking is notation is valid
    if(!NotationParser::isValidUCINotation(UCImove)){
        Logger::debug("Robot", "%s not valid UCI notation", UCImove.c_str());
        return MoveResult::InvalidNotation;
    }

    // converting UCI notation to robot coordinates
    std::pair<GridPos,GridPos> gridMove = NotationParser::UCItoGrid(UCImove);
    GridPos src = gridMove.first;
    GridPos dest = gridMove.second;
    Logger::debug("Robot", "%s => (%d,%d)->(%d,%d)", UCImove.c_str(),src.first,src.second,dest.first,dest.second);

    MoveResult result = MoveResult::OK;

    //handling "special moves"
    
    if(board.isOccupied(dest)){
        Logger::debug("Robot", "Eating a piece!");
        result = movePieceToGraveyard(dest);
    }
    else if(NotationParser::isCastling(UCImove,board.getPiece(src).type)){
        Logger::debug("Robot", "Castling!");
        result = movePiece(NotationParser::getTowerCastlingMoves(UCImove));
    }
    else if(NotationParser::isPromotion(UCImove)){
        Logger::debug("Robot", "Promoting a pawn!");
        return handlePromotion(src, dest, board.getPiece(src));
    }
    else if(NotationParser::isEnPassant(UCImove,board.getPiece(src).type)){
        Logger::debug("Robot", "En Passant!");
        result = handleEnPassant(UCImove);
    }
    if(result != MoveResult::OK){
        return result;
    }

    //Moving piece
    
    result = movePiece(src, dest);

    return result;
}

void Robot::home()
{
    motion.home();
}
