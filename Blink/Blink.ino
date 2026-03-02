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

// Realistic Cop Car Lights + Siren + Multi Fade LEDs
// --------------------------------------------------
// LED1 & LED2 alternate every 250ms
// Piezo siren sweeps frequency smoothly
// THREE LEDs fade independently using PWM
// Uses millis() so everything runs together

// ---------------- Pins ----------------
int led1 = 10;
int led2 = 9;
int piezoPin = 11;

int fadeLed1 = 6;
int fadeLed2 = 5;
int fadeLed3 = 3;

// ---------------- LED Timing ----------------
unsigned long previousLedMillis = 0;
int ledState = 0;

// ---------------- Siren Timing ----------------
unsigned long previousSirenMillis = 0;
int freq = 600;
int step = 20;
int maxFreq = 1600;
int minFreq = 600;

// ---------------- Fade LED Timing ----------------
unsigned long previousFadeMillis = 0;

// Individual brightness levels
int brightness1 = 0;
int brightness2 = 85;   // offset start positions
int brightness3 = 170;

int fadeStep1 = 5;
int fadeStep2 = 5;
int fadeStep3 = 5;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  pinMode(fadeLed1, OUTPUT);
  pinMode(fadeLed2, OUTPUT);
  pinMode(fadeLed3, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  // -----------------------------
  // Alternating LEDs (250ms)
  // -----------------------------
  if (currentMillis - previousLedMillis >= 250) {
    previousLedMillis = currentMillis;

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
  // Siren Sweep (15ms)
  // -----------------------------
  if (currentMillis - previousSirenMillis >= 15) {
    previousSirenMillis = currentMillis;

    tone(piezoPin, freq);

    freq += step;

    if (freq >= maxFreq || freq <= minFreq) {
      step = -step;
    }
  }

  // -----------------------------
  // THREE PWM Fade LEDs (20ms)
  // -----------------------------
  if (currentMillis - previousFadeMillis >= 20) {
    previousFadeMillis = currentMillis;

    // LED 1
    analogWrite(fadeLed1, brightness1);
    brightness1 += fadeStep1;
    if (brightness1 <= 0 || brightness1 >= 255) {
      fadeStep1 = -fadeStep1;
    }

    // LED 2
    analogWrite(fadeLed2, brightness2);
    brightness2 += fadeStep2;
    if (brightness2 <= 0 || brightness2 >= 255) {
      fadeStep2 = -fadeStep2;
    }

    // LED 3
    analogWrite(fadeLed3, brightness3);
    brightness3 += fadeStep3;
    if (brightness3 <= 0 || brightness3 >= 255) {
      fadeStep3 = -fadeStep3;
    }
  }
}