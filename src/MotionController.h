#pragma once
#include <CoordinateTypes.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

constexpr int STEP_PIN_X = 22;
constexpr int DIR_PIN_X  = 23;
constexpr int EN_PIN_X   = 0;

constexpr int STEP_PIN_Y = 18;
constexpr int DIR_PIN_Y  = 19;
constexpr int EN_PIN_Y   = 0;

constexpr int MAX_SPEED = 1000;
constexpr int ACCEL     = 500;

enum class Speed { SLOW = MAX_SPEED / 10, MEDIUM = MAX_SPEED / 5, FAST = MAX_SPEED };

class MotionController {
private:
    AccelStepper motorX;
    AccelStepper motorY;
    MultiStepper gantry;

public:
    MotionController();

    void setSpeed(AccelStepper& motor, Speed speed);
    void setAccel(AccelStepper& motor, int accel);

    void home();
    void movePiece(StepPos steps, Speed speed);
    void fastMove(StepPos steps);
};
