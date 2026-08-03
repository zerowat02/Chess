#include <Arduino.h>
#include "Robot.h"
#include "NetworkManager.h"
#include "NetworkConfig.h"
#include "secrets.h"
#include "Electromagnet.h" // remove

// TODO: calibrate cellSize (mm per cell) and stepsPerMm for your hardware
Electromagnet electromagnet; // remove
Robot robot(RobotConfig(40, 1));
NetworkManager net(
    WIFI_SSID, WIFI_PASSWORD,
    MQTT_BROKER, MQTT_PORT,
    MQTT_USERNAME, MQTT_PASSWORD,
    MQTT_PUBLISH_TOPIC, MQTT_SUBSCRIBE_TOPIC
);

void setup()
{
    Serial.begin(115200);
    robot.home();
    net.setMoveCallback([](const std::string& uciMove) {
        Serial.printf("Move received: %s\n", uciMove.c_str());
        MoveResult result = robot.movePiece(uciMove);
        if (result != MoveResult::OK)
            Serial.printf("Move failed: %d\n", static_cast<int>(result));
    });

    net.begin();
    Serial.println("Ready — waiting for moves");
}

void loop()
{
    // electromagnet.enable(); // remove
    // Serial.printf("Electromagnet enabled\n"); // remove
    // electromagnet.setPolarity(Polarity::NORTH); // remove
    // Serial.printf("Electromagnet polarity set to NORTH\n"); // remove
    // electromagnet.setStrength(Strength::STRONG); // remove
    // Serial.printf("Electromagnet strength set to STRONG\n"); // remove
    // delay(7000); // remove
    // electromagnet.setPolarity(Polarity::SOUTH); // remove
    // Serial.printf("Electromagnet polarity set to SOUTH\n"); // remove
    // delay(7000); // remove
    // electromagnet.disable(); // remove
    Serial.printf("Electromagnet disabled\n"); // remove
    net.loop();
}
