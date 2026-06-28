#pragma once
#include<Board.h>
#include<RobotConfig.h>
#include<StepConverter.h>
#include<PathPlanner.h>
#include<MotionController.h>
#include<NotationParser.h>
#include<Logger.h>
#include <string>

using namespace std;

enum class MoveResult { OK, InvalidNotation, GraveyardFull, PathFindingError};

class Robot
{
private:
    Board board;
    PathPlanner planner;
    MotionController motion;
    StepConverter stepConverter;
    GridPos currentPosition;

    MoveResult movePiece(GridPos src, GridPos dest);

public:
    Robot(RobotConfig cfg) : stepConverter(cfg) {}
    MoveResult movePiece(std::string UCImove);
    void home();
};




