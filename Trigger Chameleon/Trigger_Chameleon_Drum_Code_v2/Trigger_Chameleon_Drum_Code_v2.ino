/* 
  North Coast Modular Collective Trigger Chameleon
  ---------------------------------------------------------
  Copyright 2017 North Coast Modular Collective
  MIT License:
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
  documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
  the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and 
  to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of 
  the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  ----------------------------------------------------------  
  */

//For modifications, the code from the "GUItool" below can be imported into the Teensy audio system design tool at https://www.pjrc.com/teensy/gui/index.html

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=66.66666412353516,593.3333292007446
AudioSynthSimpleDrum     drum1;          //xy=86.66665649414062,208.33334255218506
AudioSynthNoiseWhite     noise1;         //xy=87.75000762939453,262.25001430511475
AudioSynthSimpleDrum     drum2;          //xy=95.66665649414062,343.33337116241455
AudioSynthNoiseWhite     noise2;         //xy=95.75,413.25001335144043
AudioEffectMultiply      multiply1;      //xy=211.75006866455078,539.2500762939453
AudioEffectMultiply      multiply2;      //xy=212.75001907348633,637.2500019073486
AudioEffectEnvelope      envelope3;      //xy=222.7500114440918,209.25001430511475
AudioEffectEnvelope      envelope5;      //xy=222.7500114440918,261.2500419616699
AudioEffectEnvelope      envelope4;      //xy=224.75001525878906,343.2500123977661
AudioEffectEnvelope      envelope6;      //xy=227.75001525878906,414.24999809265137
AudioEffectBitcrusher    bitcrusher4;    //xy=353.3334045410156,539.6666564941406
AudioEffectBitcrusher    bitcrusher5;    //xy=356.66667556762695,638.3334064483643
AudioEffectBitcrusher    bitcrusher1;    //xy=366.6667022705078,209.333327293396
AudioEffectBitcrusher    bitcrusher2;    //xy=369.6666564941406,342.3333110809326
AudioMixer4              mixer1;         //xy=537.6667098999023,228.33334350585938
AudioMixer4              mixer2;         //xy=540.6667098999023,359.3333435058594
AudioFilterStateVariable filter2;        //xy=680.8334312438965,325.8333930969238
AudioFilterStateVariable filter1;        //xy=687.9723014831543,194.9166717529297
AudioMixer4              mixer4;         //xy=828.6110801696777,358.0555953979492
AudioMixer4              mixer3;         //xy=832.7500114440918,228.25000762939453
AudioOutputI2S           i2s1;           //xy=986.2222747802734,306.44440937042236
AudioConnection          patchCord1(i2s2, 0, multiply1, 1);
AudioConnection          patchCord2(i2s2, 1, multiply2, 1);
AudioConnection          patchCord3(drum1, envelope3);
AudioConnection          patchCord4(noise1, envelope5);
AudioConnection          patchCord5(drum2, envelope4);
AudioConnection          patchCord6(noise2, envelope6);
AudioConnection          patchCord7(multiply1, bitcrusher4);
AudioConnection          patchCord8(multiply2, bitcrusher5);
AudioConnection          patchCord9(envelope3, bitcrusher1);
AudioConnection          patchCord10(envelope5, 0, mixer1, 1);
AudioConnection          patchCord11(envelope4, bitcrusher2);
AudioConnection          patchCord12(envelope6, 0, mixer2, 1);
AudioConnection          patchCord13(bitcrusher4, 0, mixer1, 2);
AudioConnection          patchCord14(bitcrusher5, 0, mixer2, 2);
AudioConnection          patchCord15(bitcrusher1, 0, mixer1, 0);
AudioConnection          patchCord16(bitcrusher1, 0, multiply1, 0);
AudioConnection          patchCord17(bitcrusher2, 0, mixer2, 0);
AudioConnection          patchCord18(bitcrusher2, 0, multiply2, 0);
AudioConnection          patchCord19(mixer1, 0, filter1, 0);
AudioConnection          patchCord20(mixer1, 0, mixer3, 2);
AudioConnection          patchCord21(mixer2, 0, filter2, 0);
AudioConnection          patchCord22(mixer2, 0, mixer4, 2);
AudioConnection          patchCord23(filter2, 0, mixer4, 0);
AudioConnection          patchCord24(filter2, 2, mixer4, 1);
AudioConnection          patchCord25(filter1, 0, mixer3, 0);
AudioConnection          patchCord26(filter1, 2, mixer3, 1);
AudioConnection          patchCord27(mixer4, 0, i2s1, 1);
AudioConnection          patchCord28(mixer3, 0, i2s1, 0);
// GUItool: end automatically generated code



AudioControlSGTL5000 codec;
//  Set up all the pin number variables
//trigger inputs
int Trigger1Pin = 5; 
int Trigger2Pin = 8; 
int Trigger3Pin = 28; 
//LEDs
int LEDA = 29;
int LEDB = 30;
int LEDC = 31;
int LEDD = 32;
int LEDE = 33;
int Trig1LED = 27;
int Trig2LED = 26;
int Trig3LED = 25;
//Switches
int SwitchA1 = 0;
int SwitchB1 = 1;
int SwitchC1 = 2;
int SwitchD1 = 3;
int SwitchE1 = 4;
//Potentiometers
int pA2 = A13;
int pB2 = A0;
int pC2 = A12;
int pD2 = A7;
int pE2 = A6;
int pA3 = A3; 
int pB3 = A11;
int pC3 = A10;
int pD3 = A1;
int pE3 = A2;

//variables for tracking the trigger states
int playTimes = 0; 
int playTimes2 = 0; 
int playTimes3 = 0;

float Drum1Level = 1.0; //Audio level appears to require a float. see if this can be an int!!!!!!!!!!!!!!
float Drum2Level = 1.0;
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup() {

// Get the board ready
  AudioMemory(200);
  codec.enable();
  codec.volume(1); //0-1. crank it. We'll control volume per drum channel with the mixers.
  codec.lineOutLevel(13); //make the codec use the maximum voltage range for output (3.16 volts p-p)
  codec.dacVolume(1);
  
//Now set up the oscillators  
  AudioNoInterrupts(); 
//Set up drum1
  drum1.frequency(60);
  drum1.length(500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.50);
//Set up drum2
  drum2.frequency(220);
  drum2.length(200);
  drum2.secondMix(0.0);
  drum2.pitchMod(0.55);

//Set up FX
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
  bitcrusher2.bits(16);
  bitcrusher2.sampleRate(44100);
  bitcrusher4.bits(16);
  bitcrusher4.sampleRate(44100);
  bitcrusher5.bits(16);
  bitcrusher5.sampleRate(44100);

//Set up Filters

//Set up noise sources
  noise1.amplitude(.5);
  noise2.amplitude(.5);

//Set up Envelopes
  envelope3.attack(.1);
  envelope3.decay(50);
  envelope3.hold(0);
  envelope3.sustain(0);
//  envelope3.release(0);
  envelope5.attack(.1);
  envelope5.decay(0);
  envelope5.hold(0);
  envelope5.sustain(0);
//  envelope5.release(0);
  envelope4.attack(.1);
  envelope4.decay(50);
  envelope4.hold(0);
  envelope4.sustain(0);
//  envelope4.release(0);
  envelope6.attack(.1);
  envelope6.decay(0);
  envelope6.hold(0);
  envelope6.sustain(0);
//  envelope6.release(0);
  
//Set up the mixers (for "Level" settings)
  mixer1.gain(0, 1); //gain(channel, level); just pass the audio through ("level" may be any floating point number from 0 to 32767)
//  mixer1.gain(1, 1);
//  mixer1.gain(2, 1);    
  mixer2.gain(0, 1); 
//  mixer2.gain(1, 1);
//  mixer2.gain(2, 1);
  mixer3.gain(0, 1); 
  mixer3.gain(1, 0);
  mixer3.gain(2, 0);
  mixer4.gain(0, 1); 
  mixer4.gain(1, 0);
  mixer4.gain(2, 0);
  
//Set up Digital Pins
//triggers
  pinMode(Trigger1Pin, INPUT); //D1 is a digital input
  pinMode(Trigger2Pin, INPUT); //D2 is a digital input
  pinMode(Trigger3Pin, INPUT); //D3 is a digital input
//LEDs  
  pinMode(LEDA, OUTPUT); 
  pinMode(LEDB, OUTPUT); 
  pinMode(LEDC, OUTPUT); 
  pinMode(LEDD, OUTPUT);
  pinMode(LEDE, OUTPUT); 
  pinMode(Trig1LED, OUTPUT);
  pinMode(Trig2LED, OUTPUT);         
  pinMode(Trig3LED, OUTPUT); 

//switches 
/*
  pinMode(SwitchA1, INPUT_PULLUP); //Switch input with internal pullup resistor  
  pinMode(SwitchB1, INPUT_PULLUP); //Switch input with internal pullup resistor
  pinMode(SwitchC1, INPUT_PULLUP); //Switch input with internal pullup resistor
  pinMode(SwitchD1, INPUT_PULLUP); //Switch input with internal pullup resistor       
  pinMode(SwitchE1, INPUT_PULLUP); //Switch input with internal pullup resistor 
  */

  AudioInterrupts();

//Board ready, flash LEDs to indicate ready state on "boot up"
digitalWrite(LEDA, HIGH); //animate cycling the LEDs on from left to right
delay(100);              
digitalWrite(LEDA, LOW);
digitalWrite(LEDB, HIGH);
delay(100);              
digitalWrite(LEDB, LOW);
digitalWrite(LEDC, HIGH);
delay(100);              
digitalWrite(LEDC, LOW);
digitalWrite(LEDD, HIGH);
delay(100);              
digitalWrite(LEDD, LOW);
digitalWrite(LEDE, HIGH);
delay(100);              
digitalWrite(LEDE, LOW);
digitalWrite(LEDD, HIGH);  //now animate cycling the LEDs on from right to left
delay(100);              
digitalWrite(LEDD, LOW);
digitalWrite(LEDC, HIGH);
delay(100);              
digitalWrite(LEDC, LOW);
digitalWrite(LEDB, HIGH);
delay(100);              
digitalWrite(LEDB, LOW);
digitalWrite(LEDA, HIGH);
delay(100); 
digitalWrite(LEDA, LOW);
delay(100);             
digitalWrite(LEDA, HIGH); //flash them all on
digitalWrite(LEDB, HIGH);
digitalWrite(LEDC, HIGH);
digitalWrite(LEDD, HIGH);
digitalWrite(LEDE, HIGH);
delay(200);              
digitalWrite(LEDA, LOW); //flash them all off
digitalWrite(LEDB, LOW); 
digitalWrite(LEDC, LOW); 
digitalWrite(LEDD, LOW); 
digitalWrite(LEDE, LOW);  
}

elapsedMillis msec1 = 0; //timing for drum1
elapsedMillis msec2 = 0; //timing for drum2

void loop() {  //Main loop for the run state
//Now get values from the knobs and pass them on to the drum parameters
//=======SET FX Parameters===========
  int D2Bits = abs(map(analogRead(pD2), 0, 1023, 1, 16) - 16); //abs and subtraction is to make it so bits/sample rate reduce as you turn the knob up
  int E2SampleRate = abs(map(analogRead(pE2), 0, 1023, 1, 44100) - 44100); 

  int D3Bits = abs(map(analogRead(pD3), 0, 1023, 1, 16) - 16); //abs and subtraction is to make it so bits/sample rate reduce as you turn the knob up
  int E3SampleRate = abs(map(analogRead(pE3), 0, 1023, 1, 44100) - 44100); 
//drum1
   bitcrusher1.bits(D2Bits); 
   bitcrusher1.sampleRate(E2SampleRate);
   bitcrusher4.bits(D2Bits); 
   bitcrusher4.sampleRate(E2SampleRate);
//drum2
   bitcrusher2.bits(D3Bits); 
   bitcrusher2.sampleRate(E3SampleRate);
   bitcrusher5.bits(D3Bits); 
   bitcrusher5.sampleRate(E3SampleRate);


//=======SET DRUM Parameters======== 


// DRUM 1
  int Drum1Freq = map(analogRead(pA2), 0, 1023, 20, 2500); 
  drum1.frequency(Drum1Freq);

//||||||||||||||||||SHAPE|||||||||||||||||||||||||||||||||
//Set the shape of the envelope so that on the potentiomenter, left of half point is a ramp up (/|) 
//and right of half point is a decay slope (|\). 
  int Drum1Length = map(analogRead(pB2), 0, 1023, 1, 2000);
  if (Drum1Length > 1000) {  //right of center
  drum1.length(Drum1Length - 1000); 
  envelope3.attack(0);
  envelope3.delay(0);
  envelope3.hold(0);
  envelope3.decay(0);
  envelope3.sustain(Drum1Length - 1000);
  }
  else{ //left of center
  drum1.length(abs(Drum1Length - 1000));   
  envelope3.sustain(0);
  envelope3.attack(abs(Drum1Length - 1000));  
  }
  
//------------DRUM 2---------------
  int Drum2Length = map(analogRead(pB3), 0, 1023, 1, 2000);
  if (Drum2Length > 1000) {  //right of center
  drum2.length(Drum2Length - 1000); 
  envelope4.attack(0);
  envelope4.delay(0);
  envelope4.hold(0);
  envelope4.decay(0);
  envelope4.sustain(Drum2Length - 1000);
  }
  else{ //left of center
  drum2.length(abs(Drum2Length - 1000));   
  envelope4.sustain(0);
  envelope4.attack(abs(Drum2Length - 1000));  
  }
  
//|||||||||||||||||MODULATION|||||||||||||||||||||||||||||||

//Set modulation knob so that at center there is no effect, left of center is "colder" and right of center is "warmer"
  int ModLevel1 = map(analogRead(pC2), 0, 1023, 1, 2000); 
  mixer3.gain(0, mapf(ModLevel1, 1, 2000, 0, 1.0));
  mixer3.gain(1, mapf(ModLevel1, 1, 2000, 1.0, 0));
     
  filter1.frequency(abs(ModLevel1 - 1000)*4);
  
  if (ModLevel1 > 1000) { //right of center
    envelope5.decay(0);
    noise1.amplitude(0);
 //  filter1.frequency(map(abs(ModLevel1 - 1000), 1, 1000, 4410, 500));
   drum1.secondMix(mapf(abs(ModLevel1 - 1000), 1, 2000, 0, 1.0));

  } 
if (ModLevel1 < 1000) { //left of center
    noise1.amplitude(mapf(abs(ModLevel1 - 1000), 1, 2000, .001, .2));
    envelope5.decay(map(abs(ModLevel1 - 1000), 1, 2000, 0, 70)); 
//  filter1.frequency(map(abs(ModLevel1 - 1000), 1, 2000, 1100, 4410));
  }


//------------DRUM 2---------------
  int ModLevel2 = map(analogRead(pC3), 0, 1023, 1, 2000); 
  mixer4.gain(0, mapf(ModLevel2, 1, 2000, 0, 1.0));
  mixer4.gain(1, mapf(ModLevel2, 1, 2000, 1.0, 0));
     
  filter2.frequency(abs(ModLevel2 - 1000)*4);
  
  if (ModLevel2 > 1000) { //right of center
    envelope6.decay(0);
    noise2.amplitude(0);
 //  filter1.frequency(map(abs(ModLevel1 - 1000), 1, 1000, 4410, 500));
   drum2.secondMix(mapf(abs(ModLevel2 - 1000), 1, 2000, 0, 1.0));

  } 
if (ModLevel2 < 1000) { //left of center
    noise2.amplitude(mapf(abs(ModLevel2 - 1000), 1, 2000, .001, .2));
    envelope6.decay(map(abs(ModLevel2 - 1000), 1, 2000, 0, 70)); 
//  filter1.frequency(map(abs(ModLevel1 - 1000), 1, 2000, 1100, 4410));
  }


//DRUM 2
  int Drum2Freq = map(analogRead(pA3), 0, 1023, 20, 2500); 
  drum2.frequency(Drum2Freq);




//====================================

//PLAY DRUM1:



if (digitalRead(Trigger1Pin) == LOW) 
{
    if (playTimes < 1){
      drum1.noteOn();   //Play the drum1 sound just once
      envelope3.noteOn(); //drum envelope
      envelope5.noteOn(); //noise source
      digitalWrite(Trig1LED, HIGH);
    playTimes = playTimes + 1;
    msec1 = 0;
    }
    if (playTimes > 1){
      playTimes = playTimes + 1;       //Chill, don't play anything, and increment
       digitalWrite(Trig1LED, LOW);
    }
if (msec1 >= 250) {
  envelope3.noteOff();
  envelope5.noteOff();
}  
} 
if ((digitalRead(Trigger1Pin) == HIGH)){
  playTimes = 0;
  digitalWrite(Trig1LED, LOW);
}

//PLAY DRUM2:

if (digitalRead(Trigger3Pin) == LOW)
{
    if (playTimes2 < 1){
      drum2.noteOn();   //Play the drum1 sound just once
      envelope4.noteOn(); //drum envelope
      envelope6.noteOn(); //noise source
      digitalWrite(Trig3LED, HIGH);
    playTimes2 = playTimes2 + 1;
    msec2 = 0;
    }
    if (playTimes2 > 1){
      playTimes2 = playTimes2 + 1;       //Chill and increment
        digitalWrite(Trig3LED, LOW);
    }
if (msec2 >= 250) {
  envelope4.noteOff();
  envelope6.noteOff();
}
} 
if ((digitalRead(Trigger3Pin) == HIGH)){
  playTimes2 = 0;
  digitalWrite(Trig3LED, LOW);
}




//  Here for troubleshooting when Trigger isn't available
/*

//DRUM2
  drum2.noteOn();
  envelope4.noteOn(); //drum envelope
  envelope6.noteOn(); //noise source
  delay(100);
  envelope4.noteOff();
  envelope6.noteOff();

//DRUM1
  drum1.noteOn();   //Play the drum1 sound just once
  envelope3.noteOn(); //drum envelope
  envelope5.noteOn(); //noise source
  delay(100);
  envelope3.noteOff();
  envelope5.noteOff();
   
 // digitalWrite(Trig3LED, HIGH); 
  delay(500);               // wait for half a second    
*/
    
} //End of main Loop
