#include <Arduino.h>
#include "MotionController.h"

MotionController mc;

void setup() {
    Serial.begin(115200);
    Serial.printf("STEP_PIN_X: %d, DIR_PIN_X: %d, STEP_PIN_Y: %d;DIR_PIN_Y: %d\n",STEP_PIN_X, DIR_PIN_X, STEP_PIN_Y, DIR_PIN_Y);

    Serial.println("TEST 1: X axis — 200 steps forward");
    mc.movePiece({200, 0}, Speed::SLOW);
    delay(500);

    Serial.println("TEST 2: Y axis — 200 steps forward");
    mc.movePiece({200, 200}, Speed::SLOW);
    delay(500);

    Serial.println("TEST 3: diagonal — 400 steps on both axes");
    mc.movePiece({400, 400}, Speed::SLOW);
    delay(500);

    Serial.println("TEST 4: home");
    mc.home();

    Serial.println("DONE");
}

void loop() {}
