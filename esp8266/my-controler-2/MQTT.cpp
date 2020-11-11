#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char * ssid = "helloworld";
const char * pass = "zhang306";
const char * broker = "192.168.0.100";
const char * outTopic = "test/out";
const char * inTopic = "test/in";

WiFiClient espClient;
PubSubClient client(espClient);
long currentTime, lastTime;
int count = 0;
char message[50];

void setupWifi(){
    delay(100);
    Serial.print("\nConnecting to ");
    Serial.print(ssid);

    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED){
        delay(100);
        Serial.print("-");
    }
    Serial.print("\nConnected to ");
    Serial.print(ssid);
}

void reconnect(){
    while(!client.connected()){
        Serial.print("\nConnecting to ");
        Serial.println(broker);
        if(client.connect("myid")){
            Serial.print("\nConnected to ");
            Serial.println(broker);
            client.subscribe(inTopic);
        }else{
            Serial.print("/nTrying to connect again...");
            delay(1000);
        }
    }
}

void callback(char * topic, byte* payload, unsigned int length){
    Serial.print("Received Message from Topic: ");
    Serial.println(topic);
    for(int i=0; i<length; i++){
        Serial.print((char)payload[i]);
    }
    Serial.println();
}
/*
void setup(){
    Serial.begin(9600);
    setupWifi();
    client.setServer(broker, 1883);
    client.setCallback(callback);
}

void loop(){
    if(!client.connected()){
        reconnect();
    }
    client.loop();
    currentTime = millis();
    if(currentTime - lastTime > 2000){
        count++;
        snprintf(message, 75, "Count: %ld", count);
        Serial.print("Sending messages: ");
        Serial.println(message);
        client.publish(outTopic, message);
        lastTime = millis();
    }
}*/
