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

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=146.66665649414062,635.3333187103271
AudioSynthSimpleDrum     drum3;          //xy=160.66665649414062,424.33331871032715
AudioSynthSimpleDrum     drum2;          //xy=162.66665649414062,343.33331871032715
AudioSynthSimpleDrum     drum1;          //xy=163.66665649414062,208.33331871032715
AudioSynthWaveformSineModulated sine_fm2;       //xy=280.6666564941406,671.3333187103271
AudioSynthWaveformSineModulated sine_fm1;       //xy=284.6666564941406,596.3333187103271
AudioEffectBitcrusher    bitcrusher1;    //xy=370.6666564941406,208.33331871032715
AudioEffectBitcrusher    bitcrusher3;    //xy=370.6666564941406,432.33331871032715
AudioEffectBitcrusher    bitcrusher2;    //xy=372.6666564941406,344.33331871032715
AudioEffectEnvelope      envelope1;      //xy=434.6666564941406,594.3333187103271
AudioEffectEnvelope      envelope2;      //xy=434.6666564941406,671.3333187103271
AudioEffectBitcrusher    bitcrusher4;    //xy=603.333381652832,591.6666498184204
AudioEffectBitcrusher    bitcrusher5;    //xy=606.666633605957,673.3333396911621
AudioMixer4              mixer1;         //xy=651.6666564941406,228.33331871032715
AudioMixer4              mixer2;         //xy=652.6666564941406,367.33331871032715
AudioOutputI2S           i2s1;           //xy=843.6666564941406,291.33331871032715
AudioConnection          patchCord1(i2s2, 0, sine_fm1, 0);
AudioConnection          patchCord2(i2s2, 1, sine_fm2, 0);
AudioConnection          patchCord3(drum3, bitcrusher3);
AudioConnection          patchCord4(drum2, bitcrusher2);
AudioConnection          patchCord5(drum1, bitcrusher1);
AudioConnection          patchCord6(sine_fm2, envelope2);
AudioConnection          patchCord7(sine_fm1, envelope1);
AudioConnection          patchCord8(bitcrusher1, 0, mixer1, 0);
AudioConnection          patchCord9(bitcrusher3, 0, mixer2, 1);
AudioConnection          patchCord10(bitcrusher2, 0, mixer2, 0);
AudioConnection          patchCord11(envelope1, bitcrusher4);
AudioConnection          patchCord12(envelope2, bitcrusher5);
AudioConnection          patchCord13(bitcrusher4, 0, mixer1, 1);
AudioConnection          patchCord14(bitcrusher5, 0, mixer2, 2);
AudioConnection          patchCord15(mixer1, 0, i2s1, 0);
AudioConnection          patchCord16(mixer2, 0, i2s1, 1);
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
//int pE2 = A6;
//int pA3 = A3; 
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
float Drum3Level = 1.0;
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup() {

// Get the board ready
  AudioMemory(50);
  codec.enable();
  codec.volume(1); //crank it. We'll control volume per drum channel with the mixers.
  
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
//Set up drum3
  drum3.frequency(220);
  drum3.length(200);
  drum3.secondMix(0.0);
  drum3.pitchMod(0.55);
//Set up FX
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
  bitcrusher2.bits(16);
  bitcrusher2.sampleRate(44100);
  bitcrusher3.bits(16);
  bitcrusher3.sampleRate(44100);
  bitcrusher4.bits(16);
  bitcrusher4.sampleRate(44100);
  bitcrusher5.bits(16);
  bitcrusher5.sampleRate(44100);
//Audio In processing
  sine_fm1.amplitude(.7);
  sine_fm1.frequency(440);
  envelope1.decay(50);
  envelope1.sustain(0);
  sine_fm2.amplitude(.7);
  sine_fm2.frequency(440);
  envelope2.decay(50);
  envelope2.sustain(0);
 // envelope1.release(0);
  
//Set up the mixers (for "Level" settings)
  mixer1.gain(0, 1); //just pass the audio through ("level" may be any floating point number from 0 to 32767)
  mixer2.gain(0, 1);
        
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

  pinMode(SwitchA1, INPUT_PULLUP); //Switch input with internal pullup resistor  
  pinMode(SwitchB1, INPUT_PULLUP); //Switch input with internal pullup resistor
  pinMode(SwitchC1, INPUT_PULLUP); //Switch input with internal pullup resistor
  pinMode(SwitchD1, INPUT_PULLUP); //Switch input with internal pullup resistor       
  pinMode(SwitchE1, INPUT_PULLUP); //Switch input with internal pullup resistor 

  AudioInterrupts();

//Board ready, flash LEDs to indicate ready state on boot up
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

void loop() {
//Now get values from the knobs and pass them on to the drum parameters
//=======SET FX Parameters===========
  int FXBits = abs(map(analogRead(pE3), 0, 1023, 1, 16) - 16); //abs and subtraction is to make it so bits/sample rate reduce as you turn the knob up
  int FXSampleRate = abs(map(analogRead(pA2), 0, 1023, 1, 44100) - 44100); 
bool SwitchB1state = digitalRead(SwitchB1);
if (SwitchB1state == LOW) {
   bitcrusher1.bits(FXBits); 
   bitcrusher1.sampleRate(FXSampleRate);
   bitcrusher4.bits(FXBits); 
   bitcrusher4.sampleRate(FXSampleRate);
   digitalWrite(LEDB, HIGH); 
} else {
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
  bitcrusher4.bits(16);
  bitcrusher4.sampleRate(44100);
  digitalWrite(LEDB, LOW);
}

bool SwitchC1state = digitalRead(SwitchC1);
if (SwitchC1state == LOW) {
   bitcrusher2.bits(FXBits); 
   bitcrusher2.sampleRate(FXSampleRate);
   bitcrusher5.bits(FXBits); 
   bitcrusher5.sampleRate(FXSampleRate);
   digitalWrite(LEDC, HIGH); 
} else {
  bitcrusher2.bits(16);
  bitcrusher2.sampleRate(44100);
  bitcrusher5.bits(16);
  bitcrusher5.sampleRate(44100);
  digitalWrite(LEDC, LOW);
}

bool SwitchD1state = digitalRead(SwitchE1);
if (SwitchD1state == LOW) {
   bitcrusher3.bits(FXBits); 
   bitcrusher3.sampleRate(FXSampleRate);
   digitalWrite(LEDD, HIGH); 
} else {
  bitcrusher3.bits(16);
  bitcrusher3.sampleRate(44100);
  digitalWrite(LEDD, LOW);
}
 

//=======SET DRUM Parameters======== 
//DRUM 1 LEVEL: 
//  Drum1Level = mapf(analogRead(A13), 0, 1023.0, 1.0, .0);
//  mixer1.gain(0, Drum1Level);

// DRUM 1
  int Drum1Freq = map(analogRead(pB2), 0, 1023, 20, 2500); 
  drum1.frequency(Drum1Freq);
  int Drum1Length = map(analogRead(pB3), 0, 1023, 1, 2000);
  drum1.length(Drum1Length); 
  envelope1.hold(Drum1Length/2);

//DRUM 2
  int Drum2Freq = map(analogRead(pC2), 0, 1023, 20, 2500); 
  drum2.frequency(Drum2Freq);
  int Drum2Length = map(analogRead(pC3), 0, 1023, 1, 2000); 
  drum2.length(Drum2Length); 

//DRUM 3
  int Drum3Freq = map(analogRead(pD2), 0, 1023, 20, 2500); 
  drum3.frequency(Drum3Freq);
  int Drum3Length = map(analogRead(pD3), 0, 1023, 1, 2000); 
  drum3.length(Drum3Length); 

//====================================

//PLAY DRUM1:

bool SwitchA1state = digitalRead(SwitchA1);
if (SwitchA1state == LOW) {
  digitalWrite(LEDA, HIGH);
} else {
  digitalWrite(LEDA, LOW);
}

if (digitalRead(Trigger1Pin) == HIGH) 
{
    if (playTimes < 1){
  
      if (SwitchA1state == LOW) {
         //drum1.noteOn();   //Play the drum1 sound just once
         envelope1.noteOn(); //Play the incoming sound on Left In
      } else {
         drum1.noteOn();   //Play the drum1 sound just once
      }
    digitalWrite(Trig1LED, LOW);
    playTimes = playTimes + 1;
    }
    if (playTimes > 1){
      playTimes = playTimes + 1;       //Chill, don't play anything, and increment
       digitalWrite(Trig1LED, HIGH);
    }
} 
if ((digitalRead(Trigger1Pin) == LOW)){
  playTimes = 0;
  digitalWrite(Trig1LED, HIGH);
  envelope1.noteOff(); 
}



//PLAY DRUM2:

if (digitalRead(Trigger2Pin) == HIGH)
{
    if (playTimes2 < 1){
      if (SwitchA1state == LOW) {
         envelope2.noteOn(); //Play the incoming sound on Right In
      } else {
         drum2.noteOn();   //Play the drum1 sound just once
      }
    digitalWrite(Trig2LED, LOW);
    playTimes2 = playTimes2 + 1;
    }
    if (playTimes2 > 1){
      playTimes2 = playTimes2 + 1;       //Chill and increment
        digitalWrite(Trig2LED, HIGH);
    }
} 
if ((digitalRead(Trigger2Pin) == LOW)){
  playTimes2 = 0;
  digitalWrite(Trig2LED, HIGH);
  envelope2.noteOff(); 
}


//PLAY DRUM3:

if (digitalRead(Trigger3Pin) == HIGH)
{
    if (playTimes3 < 1){
    drum3.noteOn();   //Play the drum2 sound just once
    digitalWrite(Trig3LED, LOW);
    playTimes3 = playTimes3 + 1;
    }
    if (playTimes3 > 1){
      playTimes3 = playTimes3 + 1;       //Chill and increment
        digitalWrite(Trig3LED, HIGH);
    }
} 
if ((digitalRead(Trigger3Pin) == LOW)){
  playTimes3 = 0;
  digitalWrite(Trig3LED, HIGH);
}




//  Here for troubleshooting when Trigger isn't available
 // drum1.noteOn();           //Play the drum note 
 // drum2.noteOn();

//digitalWrite(Trig3LED, HIGH);

//digitalWrite(TrigLED, HIGH);
 // delay(500);               // wait for half a second    



    

    
} //End of main Loop
