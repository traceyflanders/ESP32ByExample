// the Dev Board
// const byte led_gpio = 32; // the PWM pin the LED is attached to
// the Feather S3 Board
// const byte led_gpio = 10; // the PWM pin the LED is attached to
#define TAKEOFF 27  // UDP Server
#define CW 26       // for UDP Server
#define DOWN 25     // for UDP Server
#define CCW 13      // for UDP Server
#define UP 12       // for UDP Server
#define KILL 14     // for UDP Server

int upBrightness = 0;    // how bright the LED is
int downBrightness = 255;    // how bright the LED is
int upFadeAmount = 5;    // how many points to fade the LED by
int downFadeAmount = -5;    // how many points to fade the LED by
int upChannel = 0;
int downChannel = 1;

// the setup routine runs once when you press reset:
void setup() {

  // Initialize channels
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(upChannel, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(downChannel, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcAttachPin(TAKEOFF, upChannel); // assign a led pins to a channel
  ledcAttachPin(KILL, downChannel); // assign a led pins to a channel
}

// the loop routine runs over and over again forever:
void loop() {
  ledcWrite(upChannel, upBrightness); // set the brightness of the LED
  ledcWrite(downChannel, downBrightness); // set the brightness of the LED

  // change the brightness for next time through the loop:
  upBrightness = upBrightness + upFadeAmount;
  downBrightness = downBrightness + downFadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (upBrightness <= 0 || upBrightness >= 255) {
    upFadeAmount = -upFadeAmount;
  }
  if (downBrightness <= 0 || downBrightness >= 255) {
    downFadeAmount = -downFadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}