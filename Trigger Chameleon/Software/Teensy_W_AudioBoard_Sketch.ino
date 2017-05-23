#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=112.75,264
AudioSynthSimpleDrum     drum1;          //xy=116,172.85714721679688
AudioEffectBitcrusher    bitcrusher2;    //xy=282.00006103515625,264.5714111328125
AudioEffectBitcrusher    bitcrusher1;    //xy=324.14288330078125,173.2857208251953
AudioMixer4              mixer1;         //xy=500.75,187.75
AudioMixer4              mixer2;         //xy=519.75,300.75
AudioOutputI2S           i2s1;           //xy=751.25,219.75
AudioConnection          patchCord1(drum2, bitcrusher2);
AudioConnection          patchCord2(drum1, bitcrusher1);
AudioConnection          patchCord3(bitcrusher2, 0, mixer2, 0);
AudioConnection          patchCord4(bitcrusher1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer2, 0, i2s1, 1);
// GUItool: end automatically generated code



AudioControlSGTL5000 codec;
//  Set up all the pin number variables
//trigger inputs
int Trigger1Pin = 5; 
int Trigger2Pin = 8; 
//int Trigger3Pin = 28; 
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

//variables for tracking the trigger states
int playTimes = 0; 
int playTimes2 = 0; 
int triggerTimes = 0;

float Drum1Level = 1.0; //Audio level appears to require a float. see if this can be an int!!!!!!!!!!!!!!
float Drum2Level = 1.0;
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
//Set up FX
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
  bitcrusher2.bits(16);
  bitcrusher2.sampleRate(44100);
//Set up the mixers (for "Level" settings)
  mixer1.gain(0, 1); //just pass the audio through ("level" may be any floating point number from 0 to 32767)
  mixer2.gain(0, 1);
        
//Set up Digital Pins
//triggers
  pinMode(Trigger1Pin, INPUT); //D1 is a digital input
  pinMode(Trigger2Pin, INPUT); //D2 is a digital input
//  pinMode(Trigger3Pin, INPUT); //Rand Trig is a digital input
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

//Board ready, flash LEDs to indicate ready state
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
  int FXBits1 = map(analogRead(A7), 0, 1023, 1, 16); 
  bitcrusher1.bits(FXBits1);
  
  int FXSampleRate1 = map(analogRead(A6), 0, 1023, 1, 44100); 
  bitcrusher1.sampleRate(FXSampleRate1);

  int FXBits2 = map(analogRead(A1), 0, 1023, 1, 16); 
  bitcrusher2.bits(FXBits2);
  
  int FXSampleRate2 = map(analogRead(A2), 0, 1023, 1, 44100); 
  bitcrusher2.sampleRate(FXSampleRate2);
//===================================


//=======SET DRUM Parameters======== 
//DRUM 1 LEVEL: 
  Drum1Level = mapf(analogRead(A13), 0, 1023.0, 1.0, .0);
  mixer1.gain(0, Drum1Level);
// DRUM 1 FREQ: read the input on analog pin A20 (0 - 1023) for frequency:
  int Drum1Freq = map(analogRead(A0), 0, 1023, 2500, 20); 
  drum1.frequency(Drum1Freq);
// DRUM 1 LENGTH:  
  int Drum1Length = map(analogRead(A12), 0, 1023, 2000, 1);
  drum1.length(Drum1Length); 

//DRUM 2 LEVEL: 
  //Drum2Level = mapf(analogRead(A3), 0, 1023.0, 1.0, .0);
  //mixer2.gain(0, Drum2Level);
// DRUM 2 FREQ: 
  int Drum2Freq = map(analogRead(A11), 0, 1023, 2500, 20); 
  drum2.frequency(Drum2Freq);
// DRUM 2 LENGTH:  
  int Drum2Length = map(analogRead(A10), 0, 1023, 2000, 1); 
  drum2.length(Drum2Length); 

//====================================

//PLAY DRUM1:

if (digitalRead(Trigger1Pin) == HIGH)
{
    if (playTimes < 1){
    drum1.noteOn();   //Play the drum1 sound just once
    //drum2.noteOn();
    digitalWrite(Trig1LED, HIGH);
    playTimes = playTimes + 1;
    }
    if (playTimes > 1){
      playTimes = playTimes + 1;       //Chill, don't play anything, and increment
       digitalWrite(Trig1LED, LOW);
    }
} 
if ((digitalRead(Trigger1Pin) == LOW)){
  playTimes = 0;
  digitalWrite(Trig1LED, LOW);
}



//PLAY DRUM2:

if (digitalRead(Trigger2Pin) == HIGH)
{
    if (playTimes2 < 1){
    drum2.noteOn();   //Play the drum2 sound just once
    digitalWrite(Trig2LED, HIGH);
    playTimes2 = playTimes2 + 1;
    }
    if (playTimes2 > 1){
      playTimes2 = playTimes2 + 1;       //Chill and increment
        digitalWrite(Trig2LED, LOW);
    }
} 
if ((digitalRead(Trigger2Pin) == LOW)){
  playTimes2 = 0;
  digitalWrite(Trig2LED, LOW);
}


//TRIGGER RANDOM SETTINGS:
/*
while (digitalRead(Trigger3Pin) == LOW)
{
    if (triggerTimes < 1){
       //Rando the settings where they are switched on
          int bitsRandom = random(0,16);
          bitcrusher1.bits(bitsRandom); 
          
          int sampleRandom = random(1, 44100);
          bitcrusher1.sampleRate(sampleRandom);

          int frequencyRadom = random(20, 2500);
          drum1.frequency(frequencyRadom);

          int lengthRandom = random(0, 2000);
          drum1.length(lengthRandom); 

    triggerTimes = triggerTimes + 1;
    }
    if (triggerTimes > 1){
      triggerTimes = triggerTimes + 1;       //Chill and increment
    }
} 

if ((digitalRead(Trigger2Pin) == HIGH)){
  playTimes2 = 0;
}
*/

//  Here for troubleshooting when Trigger isn't available
 // drum1.noteOn();           //Play the drum note 
 // drum2.noteOn();

digitalWrite(Trig3LED, HIGH);

//digitalWrite(TrigLED, HIGH);
 // delay(500);               // wait for half a second    



    

    
} //End of main Loop
