#pragma once
#include<RobotConfig.h>
#include<CoordinateTypes.h>
#include<vector>
#include<Logger.h>
using namespace std;


class StepConverter
{
private:
    RobotConfig config;
    int cellSize; // amount of steps needed to traverse a cell
    vector <StepPos> compressGridPath(vector<GridPos> gridPath);
public:


    StepConverter(RobotConfig cfg)
        : config(cfg), cellSize((cfg.cellSize * cfg.stepsPerMm)/2) {} // cellSize is halfed because movement is calculated by half cells (for movement inbetween cells)

    vector <StepPos> GridPathTOSteps(vector<GridPos> gridPath);

    StepPos GridMoveToSteps(GridPos gridPos);
    
}; 