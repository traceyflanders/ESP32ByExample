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
#define Clone
// #define HiLetgo
// #define Huzzah
// #define DevKit
// #define FeatherS3
// #define PCB

#ifdef Huzzah
#define TOP_RED 12
#define BLUE 27
#define TOP_GREEN 33
#define BOTTOM_RED 26
#define YELLOW 25
#define BOTTOM_GREEN 4
#endif

#ifdef FeatherS3
#define TOP_RED 12
#define BLUE 11
#define TOP_GREEN 10
#define BOTTOM_RED 18
#define YELLOW 17
#define BOTTOM_GREEN 16
#endif

#ifdef DevKit
#define TOP_RED 14
#define BLUE 25
#define TOP_GREEN 33
#define BOTTOM_RED 27
#define YELLOW 27
#define BOTTOM_GREEN 32
#endif

#ifdef HiLetgo
#define TOP_RED 25
#define BLUE 33
#define TOP_GREEN 32
#define BOTTOM_RED 15
#define YELLOW 4
#define BOTTOM_GREEN 16
#endif

#ifdef Clone
#define TOP_RED 13
#define BLUE 12
#define TOP_GREEN 14
#define BOTTOM_RED 27
#define YELLOW 26
#define BOTTOM_GREEN 25
#endif

#ifdef PCB
#define TOP_RED 26
#define BLUE 25
#define TOP_GREEN 21
#define BOTTOM_RED 27
#define YELLOW 15
#define BOTTOM_GREEN 4
#endif



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }
  Serial.println("\nSerial Connected");
  pinMode(TOP_RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(TOP_GREEN, OUTPUT);
  pinMode(BOTTOM_RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BOTTOM_GREEN, OUTPUT);
  digitalWrite(TOP_RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(TOP_GREEN, LOW);
  digitalWrite(BOTTOM_RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(BOTTOM_GREEN, LOW);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(TOP_RED, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("TOP RED ON!");
  delay(2000);                 // wait for a second
  digitalWrite(TOP_RED, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("TOP RED OFF!");
  delay(2000);               // wait for a second
  digitalWrite(BLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("BLUE ON!");
  delay(2000);              // wait for a second
  digitalWrite(BLUE, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("BLUE OFF!");
  delay(2000);                    // wait for a second
  digitalWrite(TOP_GREEN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("TOP GREEN ON!");
  delay(2000);                   // wait for a second
  digitalWrite(TOP_GREEN, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("TOP GREEN OFF!");
  delay(2000);                     // wait for a second
  digitalWrite(BOTTOM_RED, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("BOTTOM RED ON!");
  delay(2000);                    // wait for a second
  digitalWrite(BOTTOM_RED, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("BOTTOM RED OFF!");
  delay(2000);                 // wait for a second
  digitalWrite(YELLOW, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("YELLOW ON!");
  delay(2000);                // wait for a second
  digitalWrite(YELLOW, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("YELLOW OFF!");
  delay(2000);                       // wait for a second
  digitalWrite(BOTTOM_GREEN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("BOTTOM GREEN ON!");
  delay(2000);                      // wait for a second
  digitalWrite(BOTTOM_GREEN, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("BOTTOM GREEN OFF!");
  delay(2000);  // wait for a second
}
