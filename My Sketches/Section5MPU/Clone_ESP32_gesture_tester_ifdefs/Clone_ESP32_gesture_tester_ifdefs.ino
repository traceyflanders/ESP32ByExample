/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define Clone
// #define HiLetgo
// #define Huzzah
// #define DevKit
// #define FeatherS3

#ifdef FeatherS3
// LED configs
#define LED_FORWARD          12
#define LED_BACK             A0
#define LED_RIGHT            10
#define LED_LEFT             11
#endif

#ifdef Clone
// LED configs
#define LED_FORWARD          12
#define LED_BACK             26
#define LED_RIGHT            14
#define LED_LEFT             13
#endif

#ifdef Huzzah
// LED configs
#define LED_FORWARD          27
#define LED_BACK             25
#define LED_RIGHT            33
#define LED_LEFT             12
#endif

MPU6050 mpu(Wire);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
unsigned long displayTimer = 0;
unsigned long serialTimer = 0;

int Roll;
int Pitch;
int Yaw;

void setup(void) {
  Serial.begin(115200);
  // Serial.setTimeout(0);
  Wire.begin();
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.clearDisplay();
  display.setCursor(0, 0);

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  display.println("MPU6050 status: ");
  display.println(status);
  display.display();
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  display.println("Hold still, don't move : ");
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  display.println("Done!");
  display.display();

  Serial.println("");
  delay(100);

  pinMode(LED_FORWARD, OUTPUT);
  pinMode(LED_BACK, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  digitalWrite(LED_FORWARD, LOW);
  digitalWrite(LED_BACK, LOW);
  digitalWrite(LED_RIGHT, LOW);
  digitalWrite(LED_LEFT, LOW);
}

void loop() {

  mpu.update();
  display.clearDisplay();
  display.setCursor(0, 0);
  Roll = mpu.getAngleX();
  Pitch = mpu.getAngleY();
  Yaw = mpu.getAngleZ();

  if (abs(Roll) <= 10) {
    digitalWrite(LED_LEFT,LOW);
    digitalWrite(LED_RIGHT,LOW);
  } 

  if (abs(Pitch) <= 15) {
    digitalWrite(LED_FORWARD,LOW);
    digitalWrite(LED_BACK,LOW);
  }

  if (Pitch < -16) {
    digitalWrite(LED_FORWARD,HIGH);
    Serial.print("F");
    if((millis()-serialTimer)>100) {
      Serial.println("orward");
      serialTimer = millis();
    }
  }

  if (Pitch > 16) {
    digitalWrite(LED_BACK,HIGH);
    Serial.print("B");
    if((millis()-serialTimer)>100) {
      Serial.println("ackward");
      serialTimer = millis();
    }
  }
  
  if (Roll < -11) {
    digitalWrite(LED_RIGHT,HIGH);
    Serial.print("R");
    if((millis()-serialTimer)>100) {
      Serial.println("ight");
      serialTimer = millis();
    }
  }
  
  if (Roll > 11) {
    digitalWrite(LED_LEFT,HIGH);
    Serial.print("L");
    if((millis()-serialTimer)>100) {
      Serial.println("eft");
      serialTimer = millis();
    }
  }
  
  
  if((millis()-displayTimer)>100){ // print data every 100ms
    display.print("Roll: ");
    display.println(Roll);
    display.print("Pitch: ");
    display.println(Pitch);
    display.print("Yaw: ");
    display.println(Yaw);
    display.display();
    
    displayTimer = millis();  
  }

}
