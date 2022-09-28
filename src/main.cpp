#include <ESP32Encoder.h>

#include <Arduino.h>
// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
hw_timer_t *timer = NULL;
unsigned long counter = 0;
unsigned long prev_counter = 0;
double velocity = 0;
ESP32Encoder encoder;
// //   avoid using pins with LEDs attached

void IRAM_ATTR onTimer(){
  // on timer interrupt.
  velocity = (counter-prev_counter) / 1000.0f;
  prev_counter = counter;
  return;
}

void setupTimerInterrupt(){
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);
  Serial.println("ESP Timer enabled");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder and Timer Test:");
  ESP32Encoder::useInternalWeakPullResistors=UP;
	// use pin 19 and 18 for the first encoder
	encoder.attachHalfQuad(19, 18);
  setupTimerInterrupt();
}


// long oldPosition  = -999;

void loop() {
  Serial.println(String(velocity, 8));
  delay(1);
  counter++;
}