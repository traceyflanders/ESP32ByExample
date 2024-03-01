/*
 Name:		Pressed.ino
 Created:	9/5/2018 10:49:52 AM
 Author:	Evert Arias
 Description: Example to demostrate how to use the library to detect a single pressed on a button.
*/

#define Clone
// #define HiLetgo
// #define Huzzah
// #define PCB
// #define DevKit
// #define FeatherS3
// #define NanoESP32

#ifdef NanoESP32
#define UP_PIN               D2
#define TAKEOFF_PIN          D4
#define CW_PIN               D3
#define CCW_PIN              A6
#define KILL_PIN             A3
#define DOWN_PIN             A7
#endif

#ifdef Clone
#define UP_PIN               32
#define TAKEOFF_PIN          33
#define CW_PIN               5
#define CCW_PIN              15
#define KILL_PIN             4
#define DOWN_PIN             18
#endif

#ifdef FeatherS3
#define UP_PIN               5
#define TAKEOFF_PIN          9
#define CW_PIN               6
#define CCW_PIN              14
#define KILL_PIN             15
#define DOWN_PIN             8
#endif

#ifdef Huzzah
#define UP_PIN               32
#define TAKEOFF_PIN          15
#define CW_PIN               21
#define CCW_PIN              16
#define KILL_PIN             17
#define DOWN_PIN             14
#endif

#ifdef PCB
#define UP_PIN               34
#define TAKEOFF_PIN          33
#define CW_PIN               32
#define CCW_PIN              39
#define KILL_PIN             36
#define DOWN_PIN             14
#endif


#include <EasyButton.h>

#define BAUDRATE 115200

// Instance of the button.
EasyButton cwButton(CW_PIN);
EasyButton ccwButton(CCW_PIN);
EasyButton takeoffButton(TAKEOFF_PIN);
EasyButton upButton(UP_PIN);
EasyButton downButton(DOWN_PIN);
EasyButton killButton(KILL_PIN);

// Callback function to be called when the button is pressed.
void onTakeoffButtonPressed()
{
  Serial.println("Takeoff Button pressed");
}

void onUpButtonPressed()
{
  Serial.println("Up Button pressed");
}

void onKillButtonPressed()
{
  Serial.println("Kill Button pressed");
}

void onDownButtonPressed()
{
  Serial.println("Down Button pressed");
}

void onCWButtonPressed()
{
  Serial.println("CW Button pressed");
}

void onCCWButtonPressed()
{
  Serial.println("CCW Button pressed");
}

void setup()
{
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);

  Serial.println();
  Serial.println(">>> EasyButton pressed example <<<");

  // Initialize each button.
  cwButton.begin();
  ccwButton.begin();
  takeoffButton.begin();
  killButton.begin();
  upButton.begin();
  downButton.begin();
  // Add the callback function to be called when each button is pressed.
  cwButton.onPressed(onCWButtonPressed);
  ccwButton.onPressed(onCCWButtonPressed);
  takeoffButton.onPressed(onTakeoffButtonPressed);
  killButton.onPressed(onKillButtonPressed);
  upButton.onPressed(onUpButtonPressed);
  downButton.onPressed(onDownButtonPressed);
}

void loop()
{
  // Continuously read the status of each button.
  takeoffButton.read();
  killButton.read();
  cwButton.read();
  ccwButton.read();
  upButton.read();
  downButton.read();
}
