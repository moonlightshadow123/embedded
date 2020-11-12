#include "MQTT.h"

WiFiClient espClient;

void default_cbk(char * topic, byte* payload, unsigned int length){
    Serial.print("Received Message from Topic: ");
    Serial.println(topic);
    for(int i=0; i<length; i++){
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

MqttClient::MqttClient(In_cbk in_cbk){
  this->client = new PubSubClient(espClient);
  this->in_cbk = in_cbk;
}

void MqttClient::reconnect(){
   while(!this->client->connected()){
        Serial.print("\nConnecting to ");
        Serial.println(broker);
        if(this->client->connect(mqtt_id)){
            Serial.print("\nConnected to ");
            Serial.println(broker);
            //if(strcmp(this->inTopic, "") != 0 && this->in_cbk != NULL)
              //this->client->subscribe(this->inTopic);
        }else{
            Serial.print("/nTrying to connect again...");
            delay(1000);
        }
    }
}

void MqttClient::begin(){
  // WiFi
  Serial.print("\nConnecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
      delay(100);
      Serial.print("-");
  }
  Serial.print("\nConnected to ");
  Serial.print(ssid);
  // PubSub
  this->client->setServer(broker, 1883);
  this->client->setCallback(default_cbk);
  this->reconnect();
}

void MqttClient::sub(const char * subTopic){
  this->reconnect();
  this->client->subscribe(subTopic);
}

void MqttClient::pub(const char * pubTopic, char * msg){
  this->reconnect();
  this->client->publish(pubTopic, msg);
}

/*
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
