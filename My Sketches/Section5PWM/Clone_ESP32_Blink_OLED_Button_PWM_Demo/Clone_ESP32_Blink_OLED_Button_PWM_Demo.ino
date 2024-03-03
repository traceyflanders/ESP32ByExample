/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <EasyButton.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// #define Huzzah
#define Clone

#ifdef Huzzah
#define BOTTOM_GREEN 4
#define TOP_RED 12
#define BLUE 27
// Arduino pins where the buttons are connected to
#define TOP_RIGHT 16
#define TOP_LEFT 15
#endif

#ifdef Clone
#define BOTTOM_GREEN 14
#define TOP_RED 27
// Arduino pins where the buttons are connected to
#define TOP_RIGHT 32
#define TOP_LEFT 33
#endif

const int rightChannel = 0;
const int leftChannel = 1;

// Button1
EasyButton button1(TOP_RIGHT);
// Button2
EasyButton button2(TOP_LEFT);

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
  display.clearDisplay();   // Clear the buffer
  display.setCursor(0, 0);  // Set cursor to the top-left corner
  display.display();
}

// Callback function to be called when button1 is pressed
void onButton1Pressed() {
  display.println("Top Right Button Pressed");
  display.println("Fading right channel");
  display.display();
  fadeLed(rightChannel);
}

// Callback function to be called when button2 is pressed
void onButton2Pressed() {
  display.println("Top Left Button Pressed");
  display.println("Fading left channel");
  display.display();
  fadeLed(leftChannel);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  Wire.begin();  // Initialize I2C communication
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.display();  // Display AdaFruit Logo
  delay(2000);        // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
  ledcSetup(leftChannel, 4000, 8);            // 12 kHz PWM, 8-bit resolution
  ledcSetup(rightChannel, 4000, 8);           // 12 kHz PWM, 8-bit resolution
  ledcAttachPin(TOP_RED, leftChannel);        // assign a led pin to a channel
  ledcAttachPin(BOTTOM_GREEN, rightChannel);  // assign a led pin to a channel

  // Initialize the button1
  button1.begin();
  // Initialize the button2
  button2.begin();
  // Add the callback function to be called when the button1 is pressed.
  button1.onPressed(onButton1Pressed);
  // Add the callback function to be called when the button2 is pressed.
  button2.onPressed(onButton2Pressed);
}

// the loop function runs over and over again forever
void loop() {
  // Continuously read the status of the buttons
  button1.read();
  button2.read();
}
