#include <WiFi.h>
#include <WebServer.h> 

const char* ssid = "shiela";
const char* password = "shielamarie";

WebServer server(80);  // Create a web server on port 80

const int ledPins[] = {15, 16, 17, 19, 21}; 
bool allOn = false;



void handleLED() {
  String request = server.uri();

  if (request.indexOf("/LED=ALL") != -1) {
    Serial.println("Toggle All LEDs");
    allOn = !allOn;
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], allOn ? HIGH : LOW);
    }
  } 
  else if (request.indexOf("/LED=32415") != -1) {
    Serial.println("Sequence 32415");
    int sequence[] = {15, 16, 17, 19, 21}; 
    for (int i = 0; i < 5; i++) {
      digitalWrite(sequence[i], HIGH);
      delay(300);
      digitalWrite(sequence[i], LOW);
    }
  } 
  else if (request.indexOf("/LED=12345") != -1) {
    Serial.println("Sequence 12345");
    one();
    two();
    three();
    two();
    one();
    clr();
  }

  server.sendHeader("Location", "/");
  server.send(303); // Redirect back to home page
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/LED=ALL", handleLED);
  server.on("/LED=32415", handleLED);
  server.on("/LED=12345", handleLED);
  
  server.begin();
}

void loop() {
  server.handleClient(); // Handle HTTP client requests
}

// Function to turn off all LEDs
void clr() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);
}

// LED Sequence Functions
void one() {
  clr();
  digitalWrite(17, HIGH);
  delay(300);
}

void two() {
  clr();
  digitalWrite(16, HIGH);
  digitalWrite(19, HIGH);
  delay(300);
}

void three() {
  clr();
  digitalWrite(15, HIGH);
  digitalWrite(21, HIGH);
  delay(300);
}