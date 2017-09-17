
#include "Talker.h"
#include "TalkerUsingSerial.h"
#include "SentenceMaker.h"

//#define DEBUG

#ifdef DEBUG
#define log(x) Serial.println(x)
// 'n' means 'no end of line'
#define logn(x) Serial.print(x)
#else
// log statements MUST NOT HAVE SIDE EFFECTS
#define log(x)
#define logn(x)
#endif

// just a simple 50ms debouncing button class

class Button {
    const byte pin;
    byte state;
    byte prevState;
    uint32_t debounce_ms;

  public:

    Button(byte attachPin) : pin(attachPin) {}

    void setup() {
      pinMode(pin, INPUT_PULLUP);
    }

    void loop() {
      prevState = state;
      if (millis() - debounce_ms >= 50) {
        state = digitalRead(pin);
        if (state != prevState) debounce_ms = millis();
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
   temperatures are measured in degrees centigrade, which I annotate as 'C'.
*/

class Burner {
    const byte sensorPin;

    // There isn't a separate pin for the relay and the indicator light
    // just drive them both off the output pin. Don't forget the current-limiting
    // resistors for the LED!

    const byte burnerPin;

    const float maxTemp_C = 30;
    const float minTemp_C = 10;
    const float hysteresis_C = .5; // half a degree
    float targetTemp_C = 18; // 18.0 degrees - a reasonable starting point

  public:
    Burner(byte sensorPinAttach, byte burnerPinAttach):
      sensorPin(sensorPinAttach), burnerPin(burnerPinAttach) {}

    void setup() {
      pinMode(burnerPin, OUTPUT);
    }

    void loop() {
      float temp_C = getSensorTemp_C();
      if (temp_C < targetTemp_C - hysteresis_C) {
#ifdef DEBUG
        if (digitalRead(burnerPin) != HIGH) {
          logn("Sensed burner temp is ");
          logn(temp_C);
          logn(" setpoint is ");
          logn(targetTemp_C);
          log(" turning burner ON.");
        }
#endif
        digitalWrite(burnerPin, HIGH);
      }
      else if (temp_C > targetTemp_C + hysteresis_C) {
#ifdef DEBUG
        if (digitalRead(burnerPin) != LOW) {
          logn("Sensed burner temp is ");
          logn(temp_C);
          logn(" setpoint is ");
          logn(targetTemp_C);
          log(" turning burner OFF.");
        }
#endif
        digitalWrite(burnerPin, LOW);
      }
    }

    float getTargetTemp_C() {
      return targetTemp_C;
    }

    // I rely on the fact that .5 is a power of 2 and so a floating point value can represent it exactly.

    void increaseTargetTemp() {
      if (targetTemp_C < maxTemp_C) targetTemp_C += .5;
    }

    void decreaseTargetTemp() {
      if (targetTemp_C > minTemp_C) targetTemp_C -= .5;
    }

  protected:

    /**
       This function calculates the sensor temperature in tenths of a degree
       centigrade.

       YOU WILL NEED TO REWRITE THIS APPROPRIATELY FOR YOUR HARDWARE

    */

    float getSensorTemp_C() {
      // I have a potentiometer on the analog input. I'll just scale it so that the sensed temp
      // winds up somewhere between zero and 50-ish.
      // analog inputs lie in a range 0 to 1023, so I'll just divide by 20.

      return analogRead(sensorPin) / 20.0;
    }
};

// Main app state and variables

enum State {
  STANDBY,
  ADJUSTING,
  WAIT_BEFORE_STANDBY
} state = STANDBY;

uint32_t timeout_ms;

const uint32_t adjustingTimeout_ms = 5000;
const uint32_t waitbeforestandbyTimeout_ms = 5000;


////////////////  PINOUT  //////////////////////////


// TODO - When you have TalkerUsingSoundcard written, substitutte that in place of TalkerUsingSerial here

TalkerUsingSerial talker;

SentenceMaker sentenceMaker(talker);

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
  sentenceMaker.setup();

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
  sentenceMaker.loop();

  boolean button = buttonUp.falling() || buttonDown.falling();

  if (button) {
    log("got a button press");
  }

  // we time the timeoust from the most recent button press or from
  // when the talker finishes talking
  if (button || talker.isTalking()) {
    timeout_ms = millis();
  }

  switch (state) {
    case STANDBY:
      if (button) {
        sentenceMaker.sayWelcomeMessage(burner.getTargetTemp_C());
        ledUp.setFlashing(true);
        ledDown.setFlashing(true);
        log("| - moving into adjusting state");
        state = ADJUSTING;
      }
      break;
    case ADJUSTING:
      if (button) {
        if (buttonUp.falling()) burner.increaseTargetTemp();
        if (buttonDown.falling()) burner.decreaseTargetTemp();
        log("| - new adjusting message");
        sentenceMaker.sayAdjustingMessage(burner.getTargetTemp_C());
      }
      else {
        if (millis() - timeout_ms >= adjustingTimeout_ms) {
          log("| - moving into wait before standing by");
          sentenceMaker.saySignoffMessage(burner.getTargetTemp_C());
          timeout_ms = millis();
          state = WAIT_BEFORE_STANDBY;
        }
      }
      break;
    case WAIT_BEFORE_STANDBY:
      if (button) {
        log("| - cancelling standby");
        sentenceMaker.sayAdjustingMessage(burner.getTargetTemp_C());
        state = ADJUSTING;
      }
      else {
        if (millis() - timeout_ms >= waitbeforestandbyTimeout_ms) {
          ledUp.setFlashing(false);
          ledDown.setFlashing(false);
          state = STANDBY;
          log("| - standing by");
        }
      }
      break;
  }
}

