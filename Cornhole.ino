/*
Laser trip light changer

100 Ohm resistor for laser
10K Ohm resistor for photocell
47 Ohm resistsor for ring
1k Ohm resistor for transistor

*/

int LASER = 13; //set up variable LASER as the pin to which the laser connects
int RING = 12; //set up the variable RING as the pin to which the led ring connects
int STRIP = 11; //set up the variable STRIP as the pin to which the led strip connects
int PHOTO = 0; //set up the variable PHOTO as the pin to which the photocell connects

int BRIGHTNESS = 255; //set the initial brightness of 255 (full)
int FADE = 5; //set the fade value
int BEAMACTIVATE = 0; //set the value

void setup() { //function that only runs once initially
  
  pinMode(LASER,OUTPUT); //set up LASER pin as OUTPUT
  pinMode(RING,OUTPUT); //set up RING pin as OUTPUT
  pinMode(STRIP,OUTPUT); //set up STRIP pin as OUTPUT
}

void loop() { //function that continues to loop
    digitalWrite(LASER,HIGH); //turn the laser on
    
    if( BEAMACTIVATE == 0 ){
    // beam is currently not activated... 
      digitalWrite(RING, HIGH); //turn RING on 
      BRIGHTNESS= 0;          //turn STRIP off 

    // check state of the beam
    if(analogRead(PHOTO) < 700){ //if analog 0 has value under 700 from photocell
      // beam has just been activated !!!
      BEAMACTIVATE = 1; 
      digitalWrite(RING, LOW); //turn RING off
      BRIGHTNESS = 255;    //turn the STRIP ON
    }
  }else{
    // beam has been activated
    // - we need to fade the STRIP

    BRIGHTNESS = BRIGHTNESS - FADE; //lower the brightness determined by FADE
    if( BRIGHTNESS <= 0 ){    //have we faded out yet ?
      BRIGHTNESS = 0;
      BEAMACTIVATE = 0;   //we aren't activated any more
    }

  }

  analogWrite(STRIP, BRIGHTNESS); //write out whatever brightness we've set
  delay(30); //delay 30 ms before looping again
}

