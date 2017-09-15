
#include "SentenceMaker.h"


void SentenceMaker::setup() {
  // no harware setup required - that kind og thing is up to the talker.
}

void SentenceMaker::loop() {
  if (message == NONE || state == STANDBY) return;
  if (state != BEGIN && talker.isTalking()) return;

  int v_abs = abs(temp_dC);
  int v_ones = v_abs / 10;
  int v_point = v_abs % 10;

  // the abels are a little confusing. each case gets called when the
  // talker has *finished* saying what the label indicates

  switch (state) {
    case BEGIN:
      switch (message) {
        case WELCOME:
          talker.sayWelcomePart1();
          break;
        case ADJUSTING:
          break;
        case SIGNOFF:
          talker.saySignoffPart1();
      }
      state = PART_1;
      break;

    case PART_1:
      // finished saying part1. need to say 'minus'
      if (temp_dC < 0) {
        talker.sayMinus();
      }
      state = MINUS;
      break;

    case MINUS:
      // finished saying minus. need to say the tens digit
      if (v_ones >= 20) {
        talker.sayTwentyToNinety(v_ones - (v_ones % 10));
        state = TENS;
      }
      else {
        talker.sayZeroToNineteen(v_ones);
        state = UNITS;
      }
      break;

    case TENS:
      // finished saying the tens digit. need to say the unit
      talker.sayZeroToNineteen(v_ones % 10);
      state = UNITS;
      break;

    case UNITS:
      if (v_point != 0) {
        talker.sayPoint();
      }
      state = POINT;
      break;

    case POINT:
      if (v_point != 0) {
        talker.sayZeroToNineteen(v_point % 10);
      }
      state = DECIMAL;
      break;
    case DECIMAL:
      switch (message) {
        case WELCOME:
          talker.sayWelcomePart2();
          break;
        case ADJUSTING:
          break;
        case SIGNOFF:
          talker.saySignoffPart2();
      }
      state = PART_2;
      break;

    case PART_2:
      talker.done();
      state = STANDBY;
      break;
  }
}

void SentenceMaker::sayWelcomeMessage(int temp_dC) {
  talker.cancel();
  message = WELCOME;
  this->temp_dC = temp_dC;
  state = BEGIN;
}

void SentenceMaker::sayAdjustingMessage(int temp_dC) {
  talker.cancel();
  message = ADJUSTING;
  this->temp_dC = temp_dC;
  state = BEGIN;
}

void SentenceMaker::saySignoffMessage(int temp_dC) {
  talker.cancel();
  message = ADJUSTING;
  this->temp_dC = temp_dC;
  state = BEGIN;
}

void SentenceMaker::cancel() {
  talker.cancel();
  message = NONE;
  this->temp_dC = temp_dC;
  state = STANDBY;
}
