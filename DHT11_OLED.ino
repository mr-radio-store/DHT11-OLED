/*
DHT11 Sensor

DHT11 Pin	Connection to Arduino
VCC	5V (or 3.3V for some models)
DATA	Pin 2 (as per #define DHTPIN 2)
GND	GND
📌 Use a 10kΩ pull-up resistor between VCC and DATA if your DHT11 module doesn’t include one.

2. SSD1306 OLED (I2C) Wiring
Your code uses I2C with Adafruit_SSD1306. The display uses:
OLED Pin	Arduino UNO
VCC	3.3V or 5V (check display voltage rating)
GND	GND
SCL	A5
SDA	A4
⚠️ Make sure you're using an I2C OLED (not SPI).

Combined Wiring Overview
Component	VCC	GND	DATA/SDA	SCL/Clock
DHT11	5V	GND	Pin 2	—
OLED I2C	3.3V/5V	GND	A4 (SDA)	A5 (SCL)

*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Pin definition for DHT11 sensor
#define DHTPIN 2     // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11 // Define sensor type as DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize the OLED display (I2C)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Initialize OLED display
  if (!display.begin(SSD1306_I2C_ADDRESS, SCREEN_WIDTH, SCREEN_HEIGHT)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear the screen
  display.clearDisplay();
  
  // Display welcome message
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("DHT11 + OLED"));
  display.display();
  delay(2000);
}

void loop() {
  // Read humidity and temperature from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if reading failed, and exit early (retry)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.print(F(" *C  Humidity: "));
  Serial.print(humidity);
  Serial.println(F(" %"));
  
  // Clear the previous display
  display.clearDisplay();
  
  // Display the values on OLED screen
  display.setCursor(0, 0);
  display.print(F("Temperature: "));
  display.print(temperature);
  display.print(F(" *C"));
  
  display.setCursor(0, 20);
  display.print(F("Humidity: "));
  display.print(humidity);
  display.print(F(" %"));
  
  display.display(); // Refresh the display
  
  // Delay before next reading
  delay(2000);  // Wait 2 seconds before the next reading
}
