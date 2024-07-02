#include <Adafruit_NeoPixel.h>
#include "DHT.h"
#include "Neopixel.h"         // Include the NeoPixel functions
#include "Distance_sensor.h"  // Include the Distance sensor functions
#include "RFID.h"             // Include the RFID functions

// Constants
#define LED_PIN 14
#define LED_COUNT 24
#define CLOSEST_DISTANCE 1
#define MAX_DISTANCE 100
#define DHTPIN 8
#define BUTTON_PIN_FOR_BUZZER 2
#define BUTTON_PIN_FOR_NEOPIXEL 3
#define DHTTYPE DHT11

// Pins for distance sensor
const int trigPin = 4;
const int buzzer = 5;
const int echoPin = 6;
const int ledPin = 7;

// LED pins for RFID
//const int redLedPin = 16; //Light on when an unauthorized card is scanned
//const int greenLedPin = 15; //Light on when an authorized card is scanned

// Global variables
bool buzzerOn = false;
bool buzzerEnabled = true;
bool neoPixelEnabled = true;

// Objects
Adafruit_NeoPixel neoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
DHT dht(DHTPIN, DHTTYPE);

// Function prototypes
void freezeBuzzer();
void controlNeoPixel();
void runNeoPixelAnimations();


void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize NeoPixel
  neoPixel.begin();
  neoPixel.show();
  neoPixel.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // Initialize DHT
  dht.begin();

  // Initialize Distance Sensor
  setupDistanceSensor();
  
  // Initialize RFID
  pinMode(16, OUTPUT); // Red LED
  pinMode(15, OUTPUT); // Green LED
  SPI.begin();          // Initiate SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  // Attach interrupt to the button pins
  pinMode(BUTTON_PIN_FOR_BUZZER, INPUT_PULLUP);
  pinMode(BUTTON_PIN_FOR_NEOPIXEL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_FOR_BUZZER), freezeBuzzer, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_FOR_NEOPIXEL), controlNeoPixel, FALLING);
}

void loop() {
  
  // Read DHT sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Uncomment this if your DHT works properly, mine is broken so I commented this out
  /*if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(2000);  
    return;
  }*/

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  // Re-check the values after every 27.4s 
  Serial.print(t);
  Serial.print(F(","));
  Serial.print(h);


  // Check distance sensor and get distance value
  int currentDistance = checkDistanceSensor();
  Serial.print(F(","));
  Serial.print(currentDistance);
  Serial.print("\n");  
  delay(1500);  

  //Turn the buzzer on if 
  //The buzzer function is enable AND the distance is less than 5
  if (buzzerEnabled && !buzzerOn && currentDistance <= 5) {
    digitalWrite(buzzer, HIGH);
    buzzerOn = true;
  }

  // If the buzzer is on, constantly check the distance sensor and stop other process such as light animation 
  while (buzzerOn) {
    int newDistance = checkDistanceSensor();
     // Only check the RFID card when the buzzer is on
    bool rfidCheck = checkRFID();
    if (newDistance > 5) {
      digitalWrite(buzzer, LOW); // Turn off buzzer if distance is safe
      buzzerOn = false;
    } else if (rfidCheck) {
      digitalWrite(buzzer, LOW); // Turn off buzzer if the authorized card is scanned
      buzzerOn = false;
      break;
    }
  }
  // Only run NeoPixel operations if it's enabled
  if (neoPixelEnabled) {
    //Map the distance value to the ring
    int numLedsToTurnOn = map(currentDistance, MAX_DISTANCE, CLOSEST_DISTANCE, 0, LED_COUNT);
    uint32_t color = numLedsToTurnOn == LED_COUNT ? 0xFF0000 : 0x00FF00;
  // Loop over all the LEDs to light up
    for (byte i = 0; i < numLedsToTurnOn; i++) {
        // Set the color to the computed color value
      neoPixel.setPixelColor(i, color);
    }
    // Loop over all the LEDs that are going to be off
    for (byte i = numLedsToTurnOn; i < LED_COUNT; i++) {
          // Turn of the LED
      neoPixel.setPixelColor(i, 0);
    }
      // call show to light it up
     neoPixel.show();
  }
} 


void freezeBuzzer() {
  buzzerEnabled = !buzzerEnabled; // Toggle the buzzer enable state
  Serial.println("Button for buzzer pressed!");

  if (!buzzerEnabled && buzzerOn) {
    digitalWrite(buzzer, LOW); // Turn off the buzzer if it's currently on
    buzzerOn = false;
  }

  delay(20); // Debounce delay
}


void controlNeoPixel() {
  neoPixelEnabled = !neoPixelEnabled; // Toggle the neo pixel LED enable state
  Serial.print("Button for neo pixel LED pressed! NeoPixel ");
  Serial.println(neoPixelEnabled ? "enabled" : "disabled");

  if (neoPixelEnabled) {
    // If NeoPixel is enabled, turn on the NeoPixel ring immediately
    runNeoPixelAnimations(); // Or any other function to initialize NeoPixel behavior
  } else {
    // If NeoPixel is disabled, turn off all LEDs immediately
    for (int i = 0; i < LED_COUNT; i++) {
      neoPixel.setPixelColor(i, 0); // Set color to black (off)
    }
    neoPixel.show(); // Update NeoPixel strip immediately
  }

  delay(20); // Debounce delay
}

void runNeoPixelAnimations() {
  // Call show to light it up
   //Run the standard NeoPixel animations. This is optional. 
  colorWipe(neoPixel, neoPixel.Color(255, 0, 0), 20); // Red
  colorWipe(neoPixel, neoPixel.Color(0, 255, 0), 20); // Green
  colorWipe(neoPixel, neoPixel.Color(0, 0, 255), 20); // Blue

  theaterChase(neoPixel, neoPixel.Color(127, 127, 127), 20); // White, half brightness
  theaterChase(neoPixel, neoPixel.Color(127, 0, 0), 20); // Red, half brightness
  theaterChase(neoPixel, neoPixel.Color(0, 0, 127), 20); // Blue, half brightness
 
  theaterChaseRainbow(neoPixel, 20); // Rainbow-enhanced theaterChase variant
   rainbow(neoPixel,1);             // Flowing rainbow cycle along the whole strip
}


