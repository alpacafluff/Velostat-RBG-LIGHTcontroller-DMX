/* FSR Velostat testing sketch.
 *  Built upon  [Adafruit FSR Example](https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr)
 */

//COLOR PADS
int rPAD = A3; // Red Pad Connected to A3
int gPAD = A2; // Green Pad Connected to A2
int bPAD = A1; // Blue Pad Connected to A1

//RGB LED light & DMX Channels of RoscoMICRO C4
int rLED = 5;      // connect RED LED leg to pin 5 (PWM pin)
// Insert RED Channel Variable here (251)
int gLED = 4;      // connect GREEN LED leg to pin 4 (PWM pin)
// Insert GREEN Channel Variable here (252)
int bLED = 3;      // connect BLUE LED leg to pin 3 (PWM pin)
// Insert BLUE Channel Variable here (253)



// Velostat values when circuits are closed
int rPADval; //FSR reading for RED pad
int gPADval; //FSR reading for GREEN pad
int bPADval; //FSR reading for BLUE pad

//Brightness of LEDs
int rLEDint; // RED LED brightness
int gLEDint; // GREEN LED brightness
int bLEDint; // BLUE LED brightness

void setup() {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);
}

void loop() {

 
      // RED pad reading
        rPADval = analogRead(rPAD);
        
        if (rPADval>20){
        Serial.print("Red PAD Value is = ");
        Serial.println(rPADval);
        }
        
        // map FSR values (0-1023) to RGB Values (0-255)
        rLEDint = map(rPADval, 0, 1023, 0, 255);
        analogWrite(rLED, rLEDint);
        delay(100);


  /*
  if (gPAD > 100)
      {
      // GREEN pad reading
          gPADval = analogRead(gPAD);
          
          if (gPADval>20){
          Serial.print("Green PAD Value is = ");
          Serial.println(gPADval);
          }
          
          // map FSR values (0-1023) to RGB Values (0-255)
          gLEDint = map(gPADval, 0, 1023, 0, 255);
          analogWrite(gLED, gLEDint);
          delay(100);
      }

  if (bPAD > 100)
      {
        // BLUE pad reading
          bPADval = analogRead(bPAD);
          if (gPADval>20){
          Serial.print("Blue PAD Value is = ");
          Serial.println(bPADval);
          }
          
          // map FSR values (0-1023) to RGB Values (0-255)
          bLEDint = map(bPADval, 0, 1023, 0, 255);
          analogWrite(bLED, bLEDint);
          delay(100);
      }
*/
}
