#include "StepConverter.h"
vector<StepPos> StepConverter::compressGridPath(vector<GridPos> gridPath)
{   
    
    return vector<StepPos>();
}

vector<StepPos> StepConverter::GridPathTOSteps(vector<GridPos> gridPath)
{
    vector<StepPos> stepsPath();

    return vector<StepPos>();
}

StepPos StepConverter::GridMoveToSteps(GridPos gridPos)
{
    StepPos steps = {gridPos.first*cellSize+config.OffsetX, gridPos.second*cellSize+config.OffsetY};

    Logger::debug("StepConverter", " Grid (%d,%d) -> Steps (%d,%d)", gridPos.first, gridPos.second, steps.first, steps.second);
    
    return steps;
    
}
