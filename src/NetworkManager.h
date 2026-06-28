#pragma once
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <functional>
#include <string>

class NetworkManager {
public:
    using MoveCallback = std::function<void(const std::string&)>;

    NetworkManager(const char* ssid, const char* password,
                   const char* broker, int port,
                   const char* mqttUser, const char* mqttPassword,
                   const char* publishTopic, const char* subscribeTopic);

    void begin();
    void loop();
    void publishMove(const std::string& uciMove);
    void setMoveCallback(MoveCallback cb);

private:
    const char* _ssid;
    const char* _password;
    const char* _mqttUser;
    const char* _mqttPassword;
    const char* _publishTopic;
    const char* _subscribeTopic;

    WiFiClientSecure _wifiClient;
    PubSubClient     _mqttClient;
    MoveCallback _moveCallback;

    void connectWifi();
    void connectMqtt();
    void handleMessage(char* topic, byte* payload, unsigned int length);

    static NetworkManager* _instance;
    static void mqttCallback(char* topic, byte* payload, unsigned int length);
};
