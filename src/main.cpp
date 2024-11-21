#include "displayHandler.h"


#define LED_PIN 8


hw_timer_t *LEDtimer = NULL;     // Pointer to LED HW timer
hw_timer_s *refreshRate = NULL;  //Pointer to refresh rate HW timer

volatile bool ledState = false;
volatile bool updateOLED = false;

// ISR for LED
void IRAM_ATTR onTimer() {
  ledState = !ledState;  // Toggle LED state
}

// Interrupt Service Routine for updating OLED screen
void IRAM_ATTR onOLEDRefresh() {
  updateOLED = true;
}

hw_timer_t *configTimer(int timerIndex, void(*fn)(), float period)
{
  hw_timer_t *timer = timerBegin(timerIndex, 80, true);  // Timer 0, prescaler 80 (1us ticks), count up
  uint64_t alarmVal = period * 1000000;  //since we have 1us ticks
  timerAttachInterrupt(timer, fn, true);  // Attach the ISR to the timer
  timerAlarmWrite(timer, alarmVal, true);  // Set the timer to trigger every 1 second (1,000,000 us)
  timerAlarmEnable(timer);  // Enable the timer alarm
  return timer;
}

void setup() {
  delay(1000); // Allow time for initialization
  OLEDInit();  // Initalise the OLED 

  pinMode(LED_PIN, OUTPUT);  // Set LED pin as an output

  // Configure the hardware timer for LED blinking
  LEDtimer = configTimer(0, &onTimer,0.1);

  // Initialize the OLED refresh rate timer
  refreshRate = configTimer(1, &onOLEDRefresh,0.5);
}

void loop() {
  static int rectX = 0;  // X-coordinate for animation
  static int rectY = 0;  // Y-coordinate for animation
  static int xDir = 1;   // X-direction for rectangle movement
  static int yDir = 1;   // Y-direction for rectangle movement

  if (updateOLED) {
    updateOLED = OLEDUpdate();
  }
  digitalWrite(LED_PIN, ledState);

}