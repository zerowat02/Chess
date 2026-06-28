#pragma once

constexpr const char* MQTT_BROKER         = "f887544391914348ad98e0039129ea3c.s1.eu.hivemq.cloud";
constexpr int         MQTT_PORT           = 8883; // TLS port

// Each board publishes on its own topic and subscribes to the opponent's.
// Swap these two values on the second board.
constexpr const char* MQTT_PUBLISH_TOPIC   = "chess/game1/board1";
constexpr const char* MQTT_SUBSCRIBE_TOPIC = "chess/game1/board2";
