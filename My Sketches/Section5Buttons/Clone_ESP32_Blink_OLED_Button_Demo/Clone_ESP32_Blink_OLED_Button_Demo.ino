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
// Arduino pin where the buttons are connected to
#define TOP_RIGHT 16
#define TOP_LEFT 15
#endif

#ifdef Clone
// #define TOP_RED 13
// #define BLUE 12
// #define TOP_GREEN 14
#define BOTTOM_RED 27
// #define YELLOW 26
#define BOTTOM_GREEN 25
// Arduino pin where the buttons are connected to
// #define UP_PIN               32
#define TAKEOFF_PIN          33
// #define CW_PIN               5
// #define CCW_PIN              15
#define KILL_PIN             4
// #define DOWN_PIN             18
#endif


// Button1
EasyButton button1(TAKEOFF_PIN);
// Button2
EasyButton button2(KILL_PIN);
// Button3
// EasyButton button3(CCW_PIN);
// // Button4
// EasyButton button4(UP_PIN);
// // Button4
// EasyButton button5(CW_PIN);
// // Button6
// EasyButton button6(DOWN_PIN);

// Callback function to be called when button1 is pressed
void onButton1Pressed() {
  Serial.println("TAKEOFF_PIN pressed");
  const int flash_led = BOTTOM_RED;
  String led_name = "BOTTOM_RED";
  digitalWrite(flash_led, HIGH);        // turn the LED on (HIGH is the voltage level)
  display.println(led_name + " LED ON");  // Print the color value on OLED display
  display.display();                  // Update the OLED display     //Reset for the next message
  delay(2000);                        // wait for a 2 seconds

  digitalWrite(flash_led, LOW);          // turn the LED off by making the voltage LOW
  display.println(led_name + " LED OFF");  // Print the color value on OLED display
  display.display();                   // Update the OLED display     //Reset for the next message
  delay(2000);                         // wait for 2 seconds
}

void onButton2Pressed() {
  Serial.println("KILL_PIN pressed");
  const int flash_led = BOTTOM_GREEN;
  String led_name = "BOTTOM_GREEN";
  digitalWrite(flash_led, HIGH);        // turn the LED on (HIGH is the voltage level)
  display.println(led_name + " LED ON");  // Print the color value on OLED display
  display.display();                  // Update the OLED display     //Reset for the next message
  delay(2000);                        // wait for a 2 seconds

  digitalWrite(flash_led, LOW);          // turn the LED off by making the voltage LOW
  display.println(led_name + " LED OFF");  // Print the color value on OLED display
  display.display();                   // Update the OLED display     //Reset for the next message
  delay(2000);                         // wait for 2 seconds
}

// void onButton3Pressed() {
//   Serial.println("CCW_PIN pressed");
//   const int flash_led = TOP_RED;
//   digitalWrite(flash_led, HIGH);        // turn the LED on (HIGH is the voltage level)
//   display.println(flash_led + " LED ON");  // Print the color value on OLED display
//   display.display();                  // Update the OLED display     //Reset for the next message
//   delay(2000);                        // wait for a 2 seconds

//   digitalWrite(flash_led, LOW);          // turn the LED off by making the voltage LOW
//   display.println(flash_led + " LED OFF");  // Print the color value on OLED display
//   display.display();                   // Update the OLED display     //Reset for the next message
//   delay(2000);                         // wait for 2 seconds
// }

// void onButton4Pressed() {
//   Serial.println("UP_PIN pressed");
//   const int flash_led = BLUE;
//   digitalWrite(flash_led, HIGH);        // turn the LED on (HIGH is the voltage level)
//   display.println(flash_led + " LED ON");  // Print the color value on OLED display
//   display.display();                  // Update the OLED display     //Reset for the next message
//   delay(2000);                        // wait for a 2 seconds

//   digitalWrite(flash_led, LOW);          // turn the LED off by making the voltage LOW
//   display.println(flash_led + " LED OFF");  // Print the color value on OLED display
//   display.display();                   // Update the OLED display     //Reset for the next message
//   delay(2000);                         // wait for 2 seconds
// }

// void onButton5Pressed() {
//   Serial.println("CW_PIN pressed");
//   const int flash_led = TOP_GREEN;
//   digitalWrite(flash_led, HIGH);        // turn the LED on (HIGH is the voltage level)
//   display.println(flash_led + " LED ON");  // Print the color value on OLED display
//   display.display();                  // Update the OLED display     //Reset for the next message
//   delay(2000);                        // wait for a 2 seconds

//   digitalWrite(flash_led, LOW);          // turn the LED off by making the voltage LOW
//   display.println(flash_led + " LED OFF");  // Print the color value on OLED display
//   display.display();                   // Update the OLED display     //Reset for the next message
//   delay(2000);                         // wait for 2 seconds
// }

// void onButton6Pressed() {
//   Serial.println("DOWN_PIN pressed");
//   const int flash_led = YELLOW;
//   digitalWrite(flash_led, HIGH);        // turn the LED on (HIGH is the voltage level)
//   display.println(flash_led + " LED ON");  // Print the color value on OLED display
//   display.display();                  // Update the OLED display     //Reset for the next message
//   delay(2000);                        // wait for a 2 seconds

//   digitalWrite(flash_led, LOW);          // turn the LED off by making the voltage LOW
//   display.println(flash_led + " LED OFF");  // Print the color value on OLED display
//   display.display();                   // Update the OLED display     //Reset for the next message
//   delay(2000);                         // wait for 2 seconds
// }

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
  // display.display();  // Display AdaFruit Logo
  // delay(2000);        // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.setCursor(0, 0);

  pinMode(BOTTOM_RED, OUTPUT);
  pinMode(BOTTOM_GREEN, OUTPUT);
  digitalWrite(BOTTOM_RED, LOW);
  digitalWrite(BOTTOM_GREEN, LOW);

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

  display.clearDisplay();   // Clear the buffer
  display.setCursor(0, 0);  // Set cursor to the top-left corner
  display.display();
  // Continuously read the status of the buttons
  button1.read();
  button2.read();
}
