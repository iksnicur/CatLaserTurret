
// Load Wi-Fi library
#include <WiFi.h>
#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_http_client.h"
#include "HTTPClient.h"

// #include /../motorAndLaserController/motorAndLaserController.ino

// Replace with your network credentials
HTTPClient http;
const char* ssid = "Stay Off This Network";
const char* password = "12345768";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

//motor control and laser control variables
const int stepsPerRevolution = 2048;  
const int maxSteps = 1024;// this represents doing a full 180
bool laserOn = false;
int horizontalCount = 0;//these count variables represent how many steps we've gone in a particular direction(can be negative), both will be limited by maxSteps
int verticalCount = 0;

//control pins
int laserPin = 12;
int hIN1 = 32;
int hIN2 = 33;
int hIN3 = 14;
int hIN4 = 13;

int vIN1 = 1;
int vIN2 = 3;
int vIN3 = 2;
int vIN4 = 15;

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);

  WiFi.localIP() = local_IP;
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  camera_config_t config;
  config.pixel_format = PIXFORMAT_JPEG; // or PIXFORMAT_GRAYSCALE ?
  http.begin("http://" + WiFi.localIP().toString()+":"+80); // Specify destination for HTTP POST request

  delay(1000);
  Serial.end();

  pinMode(laserPin, OUTPUT);//our laser pin
  //horizontal
  pinMode(hIN1, OUTPUT);
  pinMode(hIN2, OUTPUT);
  pinMode(hIN3, OUTPUT);
  pinMode(hIN4, OUTPUT);
  //vertical
  pinMode(vIN1, OUTPUT);
  pinMode(vIN2, OUTPUT);
  pinMode(vIN3, OUTPUT);
  pinMode(vIN4, OUTPUT);


}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;        // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then                // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("POST /right") >= 0) {
              for(int i = 0; i < 64; i++){
                right();
              }
            } if (header.indexOf("POST /left") >= 0) {
              for(int i = 0; i < 64; i++){
                left();
              }
            } if (header.indexOf("POST /up") >= 0) {
              for(int i = 0; i < 64; i++){
                up();
              }
            } if (header.indexOf("POST /down") >= 0) {
              for(int i = 0; i < 64; i++){
                down();
              }
            } if (header.indexOf("POST /toggle") >= 0) {
              activateOrDeactivateLaser();
            } if (header.indexOf("POST /camera") >= 0) {
//Make response to camera request and send image stream back to requester.
 




              
            }

            
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    http.end();
  }
}


void left(){
  if(horizontalCount > maxSteps * -1){
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, LOW); digitalWrite(hIN3, LOW); digitalWrite(hIN4, HIGH);
    delay(5);
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, LOW); digitalWrite(hIN4, LOW);
    delay(5);
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, LOW);
    delay(5); 
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, LOW); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, HIGH);
    delay(5);
    horizontalCount -= 1;
  }
}

void right(){
  if(horizontalCount < maxSteps){
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, LOW); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, HIGH);
    delay(5);
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, LOW);
    delay(5);
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, LOW); digitalWrite(hIN4, LOW);
    delay(5);
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, LOW); digitalWrite(hIN3, LOW); digitalWrite(hIN4, HIGH);
    delay(5);
    horizontalCount += 1;
  }
}

void down(){
  if(horizontalCount > maxSteps * -1){
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, LOW); digitalWrite(vIN3, LOW); digitalWrite(vIN4, HIGH);
    delay(5);
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, LOW); digitalWrite(vIN4, LOW);
    delay(5);
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, LOW);
    delay(5); 
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, LOW); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, HIGH);
    delay(5);
    verticalCount -= 1;
  }
}

void up(){
  if(horizontalCount < maxSteps){
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, LOW); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, HIGH);
    delay(5);
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, LOW);
    delay(5);
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, LOW); digitalWrite(vIN4, LOW);
    delay(5);
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, LOW); digitalWrite(vIN3, LOW); digitalWrite(vIN4, HIGH);
    delay(5);
    verticalCount += 1;
  }
}

void activateOrDeactivateLaser(){
  if(laserOn){
    digitalWrite(laserPin, LOW);
    laserOn = false;
  }
  else{
    digitalWrite(laserPin, HIGH);
    laserOn = true;
  }
}
