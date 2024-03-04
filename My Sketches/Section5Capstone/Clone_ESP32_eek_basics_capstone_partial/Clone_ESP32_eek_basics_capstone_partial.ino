/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <EasyButton.h>

#define Clone
// #define Huzzah

#ifdef Clone
// LED configs
#define LED_FORWARD 12
#define LED_BACK 26
#define LED_RIGHT 14
#define LED_LEFT 13
#define BOTTOM_RED 27
#define BOTTOM_GREEN 25
// Arduino pins where the buttons are connected to
#define BOTTOM_RIGHT 18
#define BOTTOM_LEFT 4
#endif

#ifdef Huzzah
// LED configs
#define LED_FORWARD 27
#define LED_BACK 25
#define LED_RIGHT 33
#define LED_LEFT 12
#define BOTTOM_RED 26
#define BOTTOM_GREEN 4
// Arduino pins where the buttons are connected to
#define BOTTOM_RIGHT 14
#define BOTTOM_LEFT 21
#endif

const int forwardChannel = 0;
const int backChannel = 1;
const int fadeChannel = 2;

// Button1
EasyButton button1(BOTTOM_RIGHT);
// Button2
EasyButton button2(BOTTOM_LEFT);

MPU6050 mpu(Wire);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
unsigned long displayTimer = 0;
unsigned long serialTimer = 0;

void fadeLed(int channel) {
int brightness = 0;        // how bright the LED is
int fadeAmount = 5;        // how many points to fade the LED by
  for (int i = 0; i <= 500; i++) {
    ledcWrite(channel, brightness);  // set the brightness of the LED on channel

    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  ledcWrite(channel, 0);
}

// Callback function to be called when button1 is pressed
void onButton1Pressed() {
  display.setTextSize(1);
  display.println("Bottom Right Button Pressed");
  display.println("Light Green LED");
  display.println("For 5 seconds");
  display.display();
  digitalWrite(BOTTOM_GREEN, HIGH);
  delay(5000);
  digitalWrite(BOTTOM_GREEN, LOW);
}

// Callback function to be called when button2 is pressed
void onButton2Pressed() {
  display.setTextSize(1);
  display.println("Bottom Left Button Pressed");
  display.println("Fade on channel");
  display.display();
  fadeLed(fadeChannel);
}

int Roll;
int Pitch;
int Yaw;
int temp;

void setup(void) {
  Serial.begin(115200);
  // Serial.setTimeout(0);
  Wire.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.display();
  delay(2000);  // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.clearDisplay();
  display.setCursor(0, 0);

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  display.print("MPU6050 status: ");
  display.println(status);
  display.display();
  while (status != 0) {}  // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  display.println("Hold still, don't move : ");
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");
  display.println("Done!");
  display.display();

  Serial.println("");
  delay(100);

  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(BOTTOM_GREEN, OUTPUT);
  digitalWrite(LED_RIGHT, LOW);
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(BOTTOM_GREEN, LOW);
  ledcSetup(forwardChannel, 4000, 8);
  ledcAttachPin(LED_FORWARD, forwardChannel);
  ledcWrite(forwardChannel, 0);
  ledcSetup(backChannel, 4000, 8);
  ledcAttachPin(LED_BACK, backChannel);
  ledcWrite(backChannel, 0);
  ledcSetup(fadeChannel, 4000, 8);
  ledcAttachPin(BOTTOM_RED, fadeChannel);
  ledcWrite(fadeChannel, 0);

  // Initialize button1
  button1.begin();
  // Initialize button2
  button2.begin();
  // Add the callback function to be called when button1 is pressed.
  button1.onPressed(onButton1Pressed);
  // Add the callback function to be called when button2 is pressed.
  button2.onPressed(onButton2Pressed);

}

void loop() {

  display.clearDisplay();
  display.setCursor(0, 0);

  // Continuously read the status of the buttons
  button1.read();
  button2.read();

  mpu.update();
  Roll = mpu.getAngleX();
  Pitch = mpu.getAngleY();
  Yaw = mpu.getAngleZ();
  temp = (1.8 * mpu.getTemp()) + 32;

  if (abs(Roll) <= 10) {
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
  }

  if (abs(Pitch) <= 10) {
    ledcWrite(forwardChannel, 0);
    ledcWrite(backChannel, 0);
  }

  if (Pitch < -10) {
    ledcWrite(forwardChannel, map(max(Pitch, -45), -45, -10, 255, 0));
    Serial.print("F");
    if ((millis() - serialTimer) > 100) {
      Serial.println("orward");
      serialTimer = millis();
    }
  }

  if (Pitch > 10) {
    ledcWrite(backChannel, map(min(Pitch, 45), 10, 45, 0, 255));
    Serial.print("B");
    if ((millis() - serialTimer) > 100) {
      Serial.println("ackward");
      serialTimer = millis();
    }
  }

  if (Roll < -11) {
    digitalWrite(LED_RIGHT, HIGH);
    Serial.print("R");
    if ((millis() - serialTimer) > 100) {
      Serial.println("ight");
      serialTimer = millis();
    }
  }

  if (Roll > 11) {
    digitalWrite(LED_LEFT, HIGH);
    Serial.print("L");
    if ((millis() - serialTimer) > 100) {
      Serial.println("eft");
      serialTimer = millis();
    }
  }


  if ((millis() - displayTimer) > 100) {  // Refresh OLED display every 100ms
    display.setTextSize(2);
    display.print("Roll: ");
    display.println(Roll);
    display.print("Pitch: ");
    display.println(Pitch);
    display.print("Yaw: ");
    display.println(Yaw);
    display.print("Temp: ");
    display.println(temp);
    display.display();

    displayTimer = millis();
  }
}
