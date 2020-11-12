#ifndef MQTT_H
#define MQTTT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* const ssid = "helloworld";
const char* const pass = "zhang306";
const char* const broker = "192.168.0.102";
const char* const voiceTopic = "msg/text";
const char* const mqtt_id = "myid";


typedef void(*In_cbk)(char * topic, byte* payload, unsigned int length);

extern WiFiClient espClient;

class MqttClient{
  public:
  In_cbk in_cbk;
  PubSubClient* client;
  MqttClient(In_cbk in_cbk);
  void begin();
  void reconnect(bool disp=false);
  void sub(const char * subTopic);
  void pub(const char * pubTopic, char * msg);
};

#endif
