#include "NetworkManager.h"
#include <Arduino.h>

NetworkManager* NetworkManager::_instance = nullptr;

NetworkManager::NetworkManager(const char* ssid, const char* password,
                               const char* broker, int port,
                               const char* mqttUser, const char* mqttPassword,
                               const char* publishTopic, const char* subscribeTopic)
    : _ssid(ssid), _password(password),
      _mqttUser(mqttUser), _mqttPassword(mqttPassword),
      _publishTopic(publishTopic), _subscribeTopic(subscribeTopic),
      _mqttClient(_wifiClient)
{
    _instance = this;
    _wifiClient.setInsecure(); // skips certificate verification — fine for a private game
    _mqttClient.setServer(broker, port);
    _mqttClient.setCallback(mqttCallback);
}

void NetworkManager::begin()
{
    connectWifi();
    connectMqtt();
}

void NetworkManager::loop()
{
    if (!_mqttClient.connected())
        connectMqtt();
    _mqttClient.loop();
}

void NetworkManager::publishMove(const std::string& uciMove)
{
    _mqttClient.publish(_publishTopic, uciMove.c_str());
}

void NetworkManager::setMoveCallback(MoveCallback cb)
{
    _moveCallback = cb;
}

void NetworkManager::connectWifi()
{
    WiFi.begin(_ssid, _password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
}

void NetworkManager::connectMqtt()
{
    while (!_mqttClient.connected()) {
        Serial.print("Connecting to MQTT...");
        if (_mqttClient.connect("ChessBoard", _mqttUser, _mqttPassword)) {
            _mqttClient.subscribe(_subscribeTopic);
            Serial.println("connected");
        } else {
            Serial.printf("failed rc=%d, retrying in 2s\n", _mqttClient.state());
            delay(2000);
        }
    }
}

void NetworkManager::handleMessage(char* topic, byte* payload, unsigned int length)
{
    if (!_moveCallback) return;
    _moveCallback(std::string(reinterpret_cast<char*>(payload), length));
}

void NetworkManager::mqttCallback(char* topic, byte* payload, unsigned int length)
{
    if (_instance) _instance->handleMessage(topic, payload, length);
}
