#include <MIDI.h>;
MIDI_CREATE_DEFAULT_INSTANCE();
const int PIN_NUM = 2;
byte pins[PIN_NUM] = {A0, A1};

const int PUSH_SHORT = 700;
const int SW_LIMIT = 710;

const int VELOCITY = 127;
byte notes [PIN_NUM] = {36, 37};

short gauge [PIN_NUM];

void setup() {
  MIDI.begin();
}

void loop() {
  boolean led_stat = false;

  for (byte i = 0 ; i < PIN_NUM ; i++)
  {
    byte sw_ret = BUTTON(i);
 
    if (sw_ret == 1)
    {
      MIDI.sendNoteOn(notes[i],VELOCITY,1);
    } else if (sw_ret == 255) {
      MIDI.sendNoteOff(notes[i],VELOCITY,1);
    } else if (sw_ret != 0) led_stat = true;
  }
}

byte BUTTON(byte num) {
  byte sw_status = 0;
 
  if (analogRead(pins[num]) > 100)
  {
    gauge[num]++;
    if (gauge[num] > SW_LIMIT) gauge[num] = SW_LIMIT; // not to over limit of counter
  } else {
    if (gauge[num] > PUSH_SHORT) sw_status = 255;
    gauge[num] = 0;
  }
 
  if (gauge[num] > PUSH_SHORT) sw_status = 2;
  else if (gauge[num] == PUSH_SHORT) sw_status = 1;
 
 
  return sw_status;
}
