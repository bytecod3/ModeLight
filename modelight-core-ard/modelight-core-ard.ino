
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
#define LEVEL2_B 13
#define LEVEL3_R 12
#define LEVEL3_G 5
#define LEVEL3_B 4

#define NUM_LEDS 9

uint8_t led_array[NUM_LEDS] = {
  LEVEL1_R,
  LEVEL1_G,
  LEVEL1_B,
  LEVEL2_R,
  LEVEL2_G,
  LEVEL2_B,
  LEVEL3_R,
  LEVEL3_B
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
const char* SSID = "Eduh";
const char* PASSWORD = "password2";

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
    if(strcmp((char*)data, "led1on") == 0){
      digitalWrite(LEVEL1_R, HIGH);
      process1_led_state = "ON";
      // notifyClients(getProcessData());
    }
	  
	  if(strcmp((char*)data, "led1off") == 0){
      digitalWrite(LEVEL1_R, LOW);
      process1_led_state = "OFF";
      // notifyClients(getProcessData());
    }
	  
	  if(strcmp((char*)data, "led2on") == 0){
		  digitalWrite(process2_led, HIGH);
      process2_led_state = "ON";
      // notifyClients(getProcessData());
    }
	  
	  if(strcmp((char*)data, "led2off") == 0){
      digitalWrite(process2_led, LOW);
      process2_led_state = "OFF";
      // notifyClients(getServoValues());
    }
      
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
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to wi-fi..");
  }

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


