// Code to upload onto ESP8266


#include <PubSubClient.h>
#include <ESP8266WiFi.h>


//EDIT THESE LINES TO MATCH YOUR SETUP
#define MQTT_SERVER "192.168.1.117"  ///YourMQTTBroker'sIP
const char* ssid = "Weems_2GHz";
const char* password = "1029384756";

char* Topic = "inTopic"; //subscribe to topic to be notified about

WiFiClient wifiClient;

void setup() {
  //initialize the light as an output and set to LOW (off)

  //start the serial line for debugging
  Serial.begin(9600);
  delay(100);


  //start wifi subsystem
  WiFi.begin(ssid, password);
  //attempt to connect to the WIFI network and then connect to the MQTT server
  reconnect();

  //wait a bit before starting the main loop
      delay(2000);
}

PubSubClient client(MQTT_SERVER, 1883, callback, wifiClient);

void loop(){

  //reconnect if connection is lost
  if (!client.connected() && WiFi.status() == 3) {reconnect();}

  //maintain MQTT connection
  client.loop();

  //MUST delay to allow ESP8266 WIFI functions to run
  delay(20); 
  
}


void callback(char* topic, byte* payload, unsigned int length) {

  //convert topic to string to make it easier to work with
  String topicStr = topic; 
  
  //Print out some debugging info
  ////Serial.println("Callback update.");
  //Serial.print("Topic: ");
  //Serial.println(topicStr);

  //turn the light off if the payload is '0' and publish to the MQTT server a confirmation message
  if (payload[0] == '0'){
    Serial.print("0");
    respond();}
  if(payload[0] == '1'){
    Serial.print("1");
    respond();}
  if (payload[0] == '2'){
    Serial.print("2");
    respond();}
  if(payload[0] == '3'){
    Serial.print("3");
    respond();}
  if (payload[0] == '4'){
    Serial.print("4");
    respond();}
  if(payload[0] == '5'){
    Serial.print("5");
    respond();}
  if (payload[0] == '6'){
    Serial.print("6");
    respond();}
  if(payload[0] == '7'){
    Serial.print("7");
    respond(); 
    }
    
}
void respond(){
  delay(5);
  if (Serial.available()) {
    //read serial as a character
    char ser = Serial.read();
  switch (ser) {
      case 'a':
  client.publish("outTopic", "Relay 1 is ON");
  break;
      case 'b':
  client.publish("outTopic", "Relay 1 is OFF");
  break;
      case 'c':
  client.publish("outTopic", "Relay 2 is ON");
  break;
      case 'd':
  client.publish("outTopic", "Relay 2 is OFF");
  break;
      case 'e':
  client.publish("outTopic", "Relay 3 is ON");
  break;
      case 'f':
  client.publish("outTopic", "Relay 3 is OFF");
  break;
      case 'g':
  client.publish("outTopic", "Relay 4 is ON");
  break;
      case 'h':
  client.publish("outTopic", "Relay 4 is OFF");
  break;
}//switch 
}//if
}//void
void reconnect() {

  //attempt to connect to the wifi if connection is lost
  if(WiFi.status() != WL_CONNECTED){
   
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  }

  //make sure we are connected to WIFI before attemping to reconnect to MQTT
  if(WiFi.status() == WL_CONNECTED){
  // Loop until we're reconnected to the MQTT server
    while (!client.connected()) {
      //Serial.print("Attempting MQTT connection...");

      // Generate client name based on MAC address and last 8 bits of microsecond counter
      String clientName;
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);

      //if connected, subscribe to the topic(s) we want to be notified about
      if (client.connect((char*) clientName.c_str())) {
        Serial.print("\tMTQQ Connected");
        client.subscribe(Topic);
      }

      //otherwise print failed for debugging
      else{Serial.println("\tFailed."); abort();}
    }
  }
}

//generate unique name from MAC addr
String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5){
      result += ':';
    }
  }

  return result;
}﻿
