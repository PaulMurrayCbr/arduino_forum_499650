
#include "Talker.h"
#include "TalkerUsingSerial.h"

// just a simple 50ms debouncing button class

class Button {
    const byte pin;
    byte state;
    byte prevState;
    byte debounce_ms; // we only need this to count to 50

  public:

    Button(byte attachPin) : pin(attachPin) {}

    void setup() {
      pinMode(pin, INPUT_PULLUP);
    }

    void loop() {
      prevState = state;
      if (((byte)millis()) - debounce_ms >= 50) {
        state = digitalRead(pin);
        if (state != prevState) debounce_ms = (byte)millis();
      }
    }

    boolean falling() {
      return (state == LOW) && (prevState != LOW);
    }
};

// an LED that can be flashing or on
class FlashingLED {
    const byte pin;
    boolean flashing;

  public:
    FlashingLED(byte attachPin) : pin(attachPin) {}

    void setup() {
      pinMode(pin, OUTPUT);
    }

    void loop() {
      if (flashing) {
        // I do this the easy way: just grab bit 9 of millis()
        digitalWrite(pin,  (millis() & (1 << 9)) ? HIGH : LOW);
      }
      else {
        digitalWrite(pin, HIGH);
      }
    }

    void setFlashing(boolean f) {
      flashing = f;
    }
};

/**
    this object works the furnace. It has a sensor pin, a burner output pin, and a current setpoint value.
   temperatures are measured in tenths of a degree centigrade, which I annotate as 'dC'. I do this so that we can get
   .5 of a degree without having roundoff errors and things like that.
*/

class Burner {
    const byte sensorPin;

    // There isn't a separate pin for the relay and the indicator light
    // just drive them both off the output pin. Don't forget the current-limiting
    // resistors for the LED!

    const byte burnerPin;

    // THIS IS IN TENTHS OF A DEGREE!!!!
    const int maxTemp_dC = 350; // 35.0 degrees
    const int minTemp_dC = 50; // 5.0 degrees
    const int hysteresis_dC = 5; // half a degree
    int targetTemp_dC = 180; // 18.0 degrees - a reasonable starting point

  public:
    Burner(byte sensorPinAttach, byte burnerPinAttach):
      sensorPin(sensorPinAttach), burnerPin(burnerPinAttach) {}

    void setup() {
      pinMode(burnerPin, OUTPUT);
    }

    void loop() {
      int temp_dC = getSensorTemp_dC();
      if (temp_dC < targetTemp_dC - hysteresis_dC) {
        digitalWrite(burnerPin, HIGH);
      }
      else if (temp_dC > targetTemp_dC + hysteresis_dC) {
        digitalWrite(burnerPin, LOW);
      }
    }

    int getTargetTemp_dC() {
      return targetTemp_dC;
    }

    void increaseTargetTemp() {
      if (targetTemp_dC < maxTemp_dC) targetTemp_dC += 5;
    }

    void decreaseTargetTemp() {
      if (targetTemp_dC > minTemp_dC) targetTemp_dC -= 5;
    }

  protected:

    /**
       This function calculates the sensor temperature in tenths of a degree
       centigrade.

       YOU WILL NEED TO REWRITE THIS APPROPRIATELY FOR YOUR HARDWARE

    */

    int getSensorTemp_dC() {
      // I have a potentiometer on the analog input. I'll just scale it so that the sensed temp
      // winds up somewhere between zero and 50-ish.
      // analog inputs lie in a range 0 to 1023, so I'll just divide by 2.

      return analogRead(sensorPin) / 2;
    }
};

// Main app state and variables

enum State {
  STANDBY, 
  ADJUSTING, 
  WAIT_BEFORE_STANDBY
} state = STANDBY;

uint32_t state_ms;

const uint32_t adjustingTimeout_ms = 5000;
const uint32_t waitbeforestandbyTimeout_ms = 5000;

////////////////  PINOUT  //////////////////////////

TalkerUsingSerial talker;

Button buttonUp(11), buttonDown(10);
FlashingLED ledUp(6), ledDown(5);
Burner burner(A0, 7);


void setup() {
  buttonUp.setup();
  buttonDown.setup();
  ledUp.setup();
  ledDown.setup();
  burner.setup();
  talker.setup();
  
  ledUp.setFlashing(false);
  ledDown.setFlashing(false);
}

void loop() {
  buttonUp.loop();
  buttonDown.loop();
  ledUp.loop();
  ledDown.loop();
  burner.loop();
  talker.loop();
  
}
