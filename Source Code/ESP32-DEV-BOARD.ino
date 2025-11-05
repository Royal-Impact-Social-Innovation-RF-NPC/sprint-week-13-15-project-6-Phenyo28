#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Servo and LED Setup
Servo servoRed;
Servo servoBlue;
Servo servoYellow;

// Servo pins
const int servoRedPin = 12;
const int servoBluePin = 14;
const int servoYellowPin = 13;

// LED pins
const int ledRed = 25;
const int ledBlue = 26;
const int ledYellow = 27;

// OLED Display Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

typedef struct struct_message {
  char waste[32];
} struct_message;

struct_message data;

String waste = "";
bool gotData = false;

// Callback when data is received
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));   // Copy received data
  waste = String(data.waste);                  // Convert to String
  waste.trim();
  gotData = true;
  Serial.print("Received waste type: ");
  Serial.println(waste);
}

// Setup
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  // Initialize Servos 
  servoRed.attach(servoRedPin);
  servoBlue.attach(servoBluePin);
  servoYellow.attach(servoYellowPin);

  // Initialize LEDs 
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledYellow, LOW);

  // Initialize OLED
  if (!display  .begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Bin Starting...");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Waiting for detection...");
  display.display();

  Serial.println("Smart Bin Receiver Ready. Waiting for detection...");

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

// Loop
void loop() {
  if (gotData) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  if (waste == "paper") {
    Serial.println("Opening BLUE bin for PAPER...");
    display.println("Opening BLUE bin...");
    display.display();

    digitalWrite(ledBlue, HIGH);
    servoBlue.write(125);
    delay(3000);
    servoBlue.write(0);
    delay(1000);
    digitalWrite(ledBlue, LOW);
  }

  else if (waste == "plastic") {
    Serial.println("Opening YELLOW bin for PLASTIC...");
    display.println("Opening YELLOW bin...");
    display.display();

    digitalWrite(ledYellow, HIGH);
    servoYellow.write(125);
    delay(3000);
    servoYellow.write(0);
    delay(1000);
    digitalWrite(ledYellow, LOW);
  }

  else if (waste == "electronic waste" || waste == "e-waste" || waste == "electronics") {
    Serial.println("Opening RED bin for ELECTRONIC WASTE...");
    display.println("Opening RED bin...");
    display.display();

    digitalWrite(ledRed, HIGH);
    servoRed.write(125);
    delay(3000);
    servoRed.write(0);
    delay(1000);
    digitalWrite(ledRed, LOW);
  }

  else {
    Serial.print("Unknown waste type: ");
    Serial.println(waste);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Unknown waste type");
    display.display();
    delay(2000);
  }

  // After each action, return to waiting screen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Waiting for detection...");
  display.display();
  Serial.println("Waiting for detection...");

  }
  delay(2000);
}
