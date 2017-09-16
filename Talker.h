/**
   A Talker is a thing that knows how to say the fragments of sentences that are going to be required
   by this sketch.

   We have two implementations - a TalkerUsingSerial, which simulates what a soundcard does by
   spitting out text slowly to the serial output, and a TalkerUsingSoundcard, which is not written yet.

   The spec I am working to is o the messageboad thread:

   - press any button. Get a 'welcome chime' and the current space temp read out e.g. "Bing bong, it is twenty one point five degrees"
   - at 'welcome chime' both LEDS (red & blue) would start flashing and a voice would say,
     "To raise the temperature press the red button, to lower the temperature press the blue button"
   - when either button is pressed the set point is moved up/down by 0.5 degrees centigrade and the new set point temp is read out.
     If the button is pressed quickly, the current announcement is curtailed and the new value read out.
   - after 5 seconds of no further presses it announces, "The new set point is XX.X)
*/

#ifndef TALKER_H
#define TALKER_H

#include <Arduino.h>

class Talker {
  public:

    /**
        a talker has a setup and loop. setup gets invoked by the main sketch at setup time, loop
        gets invoked by the main sketch frequently
    */
    virtual void setup() = 0;
    virtual void loop() = 0;

    /**
       a talker can have its talking cut short.
    */

    virtual void cancel() = 0;

    /**
        when the talkng is done, this function might be used to turn speakers off, that kind of thing.
    */

    virtual void done() = 0;

    /**
       A talker takes a while to finish talking. This function tells soeone using the talker
       if the current phrase has been finished.
    */

    virtual boolean isTalking() = 0;

    virtual void sayWelcomePart1() = 0; // Bing bong, it is
    virtual void sayWelcomePart2() = 0; // degrees. To raise the temperature press the red button, to lower the temperature press the blue button

    virtual void saySignoffPart1() = 0; // The new set point is
    virtual void saySignoffPart2() = 0; // degrees.

    // will say a number between 10 and 30 in increments of .5 degrees
    virtual void sayNumber(int number, boolean pointFive) = 0; 

};

#endif

