#include "MotionController.h"


void MotionController::enable()
{
    digitalWrite(EN_PIN_X,LOW);
    digitalWrite(EN_PIN_Y,LOW);
}

void MotionController::disable()
{
    digitalWrite(EN_PIN_X,HIGH);
    digitalWrite(EN_PIN_Y,HIGH);
}

MotionController::MotionController()
    : motorX(AccelStepper::DRIVER, STEP_PIN_X, DIR_PIN_X),
      motorY(AccelStepper::DRIVER, STEP_PIN_Y, DIR_PIN_Y)
{
    motorX.setMaxSpeed(MAX_SPEED);
    motorX.setAcceleration(ACCEL);
    motorY.setMaxSpeed(MAX_SPEED);
    motorY.setAcceleration(ACCEL);
    gantry.addStepper(motorX);
    gantry.addStepper(motorY);
    pinMode(EN_PIN_X,OUTPUT);
    pinMode(EN_PIN_Y,OUTPUT);
    disable();
}

void MotionController::setSpeed(AccelStepper& motor, Speed speed) {
    motor.setMaxSpeed(static_cast<float>(speed));
}

void MotionController::setAccel(AccelStepper& motor, int accel) {
    motor.setAcceleration(accel);
}

void MotionController::movePiece(StepPos steps, Speed speed) {
    setSpeed(motorX, speed);
    setSpeed(motorY, speed);
    long target[2] = { steps.first, steps.second };
    gantry.moveTo(target);
    gantry.runSpeedToPosition();
}

void MotionController::fastMove(StepPos steps) {
    motorX.runToNewPosition(steps.first);
    motorY.runToNewPosition(steps.second);
}

void MotionController::home() {
    StepPos home = {0,0};
    movePiece(home, Speed::SLOW);
}
