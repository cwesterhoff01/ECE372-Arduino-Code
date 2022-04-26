#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>
#include <timer.h>
#include <lcd.h>
#include <SPI.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
//Pin #2 on arduino board

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

//Enum for the emoji states
typedef enum {
  HOT,
  HUMID,
  SMILE
} emojiType;

volatile emojiType faceState = SMILE; 


void setup() {
  

  SPI_MASTER_Init(); // initialize SPI module and set the data rate
  // initialize 8 x 8 LED array (info from MAX7219 datasheet)
  write_execute(0x0A, 0x08);  // brightness control
  write_execute(0x0B, 0x07); // scanning all rows and columns
  write_execute(0x0C,0x01); // set shutdown register to normal operation (0x01)
  write_execute(0x0F, 0x00); // display test register - set to normal operation (0x01)


  initLCD();
  sei(); // Enable global interrupts.
  moveCursor(0, 0); // moves the cursor to 0,0 position
  writeString("Current mode: ");
  moveCursor(1, 0);  // moves the cursor to 1,0 position



  Serial.begin(9600);
  // Initialize device.
  writeString("Is this thing on?");
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  Serial.flush();
  delayMS = sensor.min_delay / 1000;

  

}

 void loop() {
    // Delay between measurements.
    delayMs(delayMS);

  //Switch statement for face states
  switch(faceState){
      case HOT:
        //sun emoji
        write_execute(0x01, 0b10010001); // row 1 LEDS
        write_execute(0x02, 0b01001010); // row 2 LEDS 
        write_execute(0x03, 0b00111100); // row 3 LEDS
        write_execute(0x04, 0b10111110); // row 4 LEDS
        write_execute(0x05, 0b01111101); // row 5 LEDS
        write_execute(0x06, 0b00111100); // row 6 LEDS
        write_execute(0x07, 0b01010010); // row 7 LEDS
        write_execute(0x08, 0b10001001); // row 8 LEDS
      break;
      case HUMID:
        //raindrop emoji
        write_execute(0x01, 0b00000000); // row 1 LEDS
        write_execute(0x02, 0b00010000); // row 2 LEDS 
        write_execute(0x03, 0b00011000); // row 3 LEDS
        write_execute(0x04, 0b00111100); // row 4 LEDS
        write_execute(0x05, 0b01111110); // row 5 LEDS
        write_execute(0x06, 0b01111110); // row 6 LEDS
        write_execute(0x07, 0b00111100); // row 7 LEDS
        write_execute(0x08, 0b00000000); // row 8 LEDS
      break;
      case SMILE:
        //smiley face
        write_execute(0x01, 0b00000000); // row 1 LEDS
        write_execute(0x02, 0b00100100); // row 2 LEDS 
        write_execute(0x03, 0b00100100); // row 3 LEDS
        write_execute(0x04, 0b00100100); // row 4 LEDS
        write_execute(0x05, 0b10000001); // row 5 LEDS
        write_execute(0x06, 0b01000010); // row 6 LEDS
        write_execute(0x07, 0b00111100); // row 7 LEDS
        write_execute(0x08, 0b00000000); // row 8 LEDS
      break;
  }




    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println("Error reading temperature!");
    }
    else {
      Serial.print("Temperature: ");
      Serial.print(event.temperature);
      Serial.println("°C");
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
      Serial.flush();
    }

    if (event.temperature){
      //change face state
    }
    if (event.relative_humidity){
      //change face state
    }

    
  }
