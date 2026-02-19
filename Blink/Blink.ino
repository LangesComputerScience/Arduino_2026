/*
  Blink

  Developer: Mr. Lange
  Date: 2.13.2026
  
  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

// the setup function runs once when you press reset or power the board
// ----------------------------------------
// ----------------------------------------
// Realistic Cop Car Lights + Siren Project
// Smooth siren sound (fast frequency sweep)
// Slower LED blinking (250ms)
// Uses millis() so sound + lights work together
// ----------------------------------------

int led1 = 10;
int led2 = 9;
int piezoPin = 11;

// Variables for LED timing
unsigned long previousLedMillis = 0;
int ledState = 0;  // 0 = LED1 on, 1 = LED2 on

// Variables for siren timing
unsigned long previousSirenMillis = 0;
int freq = 600;         // starting frequency
int step = 20;          // how fast the frequency changes
int maxFreq = 1600;
int minFreq = 600;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // -----------------------------
  // LED Blinking (250ms timing)
  // -----------------------------
  if (currentMillis - previousLedMillis >= 250) {
    previousLedMillis = currentMillis;

    // Toggle between the two LEDs
    if (ledState == 0) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      ledState = 1;
    } 
    else {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      ledState = 0;
    }
  }

  // -----------------------------
  // Siren Sound (fast timing)
  // -----------------------------
  if (currentMillis - previousSirenMillis >= 15) {
    previousSirenMillis = currentMillis;

    tone(piezoPin, freq);  // Play tone at current frequency

    // Change the frequency
    freq += step;

    // Reverse direction at limits (up/down sweep)
    if (freq >= maxFreq || freq <= minFreq) {
      step = -step;  // reverse sweep direction
    }
  }
}

