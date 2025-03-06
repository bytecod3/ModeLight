
#include "SPIFFS.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>

// define pins 
#define LEVEL1_R 21
#define LEVEL1_G 19
#define LEVEL1_B 18
#define LEVEL2_R 15
#define LEVEL2_G 14
#define LEVEL2_B 27
#define LEVEL3_R 12
#define LEVEL3_G 5
#define LEVEL3_B 16
#define LVL_G 26

#define NUM_LEDS 10

uint8_t led_array[NUM_LEDS] = {
  LEVEL1_R,
  LEVEL1_G,
  LEVEL1_B,
  LEVEL2_R,
  LEVEL2_G,
  LEVEL2_B,
  LEVEL3_R,
  LEVEL3_G,
  LEVEL3_B,
  LVL_G
};

/**
 * Initialize hardware
 */
void init_hw(void) {
  for(int i=0; i < NUM_LEDS; i++ ) {
    pinMode(led_array[i], OUTPUT);
  }

  // initially all LEDs are OFF
  for(int i=0; i < NUM_LEDS; i++ ) {
    digitalWrite(led_array[i], LOW);
  }

}

// Replace with your network credentials
//const char* SSID = "Eduh";
//const char* PASSWORD = "password2";
const char* SSID = "AJMAL HOMES MODEL";

// pin assignments
String process1_led_state = "OFF";
String process2_led_state = "OFF";
const int process2_led = 4;

// string to hold the received message
String message = "";

// create web server object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // this object called ws handles connections on the '/ws' path

// variable to hold servo angle value
JsonDocument process_data;

// String getProcessData(){
//   // get the servo angle
//   process_data["servo_value"] = String(servo_angle);
  
//   // LED states
//   process_data["led1state"] = String(process1_led_state);
//   process_data["led2state"] = String(process2_led_state);
  
//   String process_states = JSON.stringify(process_data);
//   return process_states;
// }

void notifyClients(String servo_angles){
  ws.textAll(String(process1_led_state));
  ws.textAll(String(process2_led_state));
  ws.textAll(String(servo_angles));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
	
	  message = (char*)data;

    // check the message received depending on what was sent from the web page
    ///////////////// LEVEL 1 /////////////////////////////////
    if(strcmp((char*)data, "led1on") == 0){
      digitalWrite(LEVEL1_R, HIGH);
      digitalWrite(LEVEL1_G, HIGH);
      digitalWrite(LEVEL1_B, HIGH);
      process1_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "led1off") == 0){
      digitalWrite(LEVEL1_R, LOW);
      digitalWrite(LEVEL1_G, LOW);
      digitalWrite(LEVEL1_B, LOW);
      process1_led_state = "OFF";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledR1on") == 0){
      digitalWrite(LEVEL1_R, HIGH);
      process1_led_state = "ON";
      // notifyClients(getProcessData());
    }
	  
	  if(strcmp((char*)data, "ledR1off") == 0){
      digitalWrite(LEVEL1_R, LOW);
      process1_led_state = "OFF";
      // notifyClients(getProcessData());
    }
	  
	  if(strcmp((char*)data, "ledG1on") == 0){
		  digitalWrite(LEVEL1_G, HIGH);
      process2_led_state = "ON";
      // notifyClients(getProcessData());
    }
	  
	  if(strcmp((char*)data, "ledG1off") == 0){
      digitalWrite(LEVEL1_G, LOW);
      process2_led_state = "OFF";
      // notifyClients(getServoValues());
    }

    if(strcmp((char*)data, "ledB1on") == 0){
      digitalWrite(LEVEL1_B, HIGH);
      process2_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledB1off") == 0){
      digitalWrite(LEVEL1_B, LOW);
      process2_led_state = "OFF";
      // notifyClients(getServoValues());
    }

    ///////////////// END OF LEVEL 1 /////////////////////////////////



    ///////////////// LEVEL 2 /////////////////////////////////
    if(strcmp((char*)data, "led2on") == 0){
      digitalWrite(LEVEL2_R, HIGH);
      digitalWrite(LEVEL2_G, HIGH);
      digitalWrite(LEVEL2_B, HIGH);
      process1_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "led2off") == 0){
      digitalWrite(LEVEL2_R, LOW);
      digitalWrite(LEVEL2_G, LOW);
      digitalWrite(LEVEL2_B, LOW);
      process1_led_state = "OFF";
      // notifyClients(getProcessData());
    }

    if(strcmp((char*)data, "ledR2on") == 0){
      digitalWrite(LEVEL2_R, HIGH);
      process1_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledR2off") == 0){
      digitalWrite(LEVEL2_R, LOW);
      process1_led_state = "OFF";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledG2on") == 0){
      digitalWrite(LEVEL2_G, HIGH);
      process2_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledG2off") == 0){
      digitalWrite(LEVEL2_G, LOW);
      process2_led_state = "OFF";
      // notifyClients(getServoValues());
    }

    if(strcmp((char*)data, "ledB2on") == 0){
      digitalWrite(LEVEL2_B, HIGH);
      process2_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledB2off") == 0){
      digitalWrite(LEVEL2_B, LOW);
      process2_led_state = "OFF";
      // notifyClients(getServoValues());
    }


    ///////////////// END OF LEVEL 2 /////////////////////////////////



    ///////////////// LEVEL 3 /////////////////////////////////
    if(strcmp((char*)data, "led3on") == 0){
      digitalWrite(LEVEL3_R, HIGH);
      digitalWrite(LEVEL3_G, HIGH);
      digitalWrite(LEVEL3_B, HIGH);
      process1_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "led3off") == 0){
      digitalWrite(LEVEL3_R, LOW);
      digitalWrite(LEVEL3_G, LOW);
      digitalWrite(LEVEL3_B, LOW);
      process1_led_state = "OFF";
      // notifyClients(getProcessData());
    }

    if(strcmp((char*)data, "ledR3on") == 0){
      digitalWrite(LEVEL3_R, HIGH);
      process1_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledR3off") == 0){
      digitalWrite(LEVEL3_R, LOW);
      process1_led_state = "OFF";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledG3on") == 0){
      digitalWrite(LEVEL3_G, HIGH);
      process2_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledG3off") == 0){
      digitalWrite(LEVEL3_G, LOW);
      process2_led_state = "OFF";
      // notifyClients(getServoValues());
    }

    if(strcmp((char*)data, "ledB3on") == 0){
      digitalWrite(LEVEL3_B, HIGH);
      process2_led_state = "ON";
      // notifyClients(getProcessData());
    }
    
    if(strcmp((char*)data, "ledB3off") == 0){
      digitalWrite(LEVEL3_B, LOW);
      process2_led_state = "OFF";
      // notifyClients(getServoValues());
    }


    ///////////////// END OF LEVEL 3 /////////////////////////////////

  }

}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }

}


void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void initSPIFFS(){
   // initialize spiffs filesystem
  if(!SPIFFS.begin(true)){
    Serial.println("Error mounting SPIFFS");
  }else{
	Serial.println("SPIFFS mount success!");
  }
}

void initWIFI(){
  // Connect to Wi-Fi
//  WiFi.begin(SSID, PASSWORD);

  WiFi.softAP(SSID);
  
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(1000);
//    Serial.println("Connecting to wi-fi..");
//  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

}


void setup() {
  Serial.begin(115200);
  init_hw();

  // mount file system
  initSPIFFS();
  
  initWIFI();
  
  initWebSocket();
	
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  //serve static files from server
  server.serveStatic("/", SPIFFS, "/");
  
  // Start server
  server.begin();

}

void loop() {
  ws.cleanupClients();
}
