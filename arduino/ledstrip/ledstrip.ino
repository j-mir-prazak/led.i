// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!


#include <avr/wdt.h>
 
#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11

bool serialConnected = true;
double ledTimeout = 2500;

String serialInput = "";

int r, g, b;
int stateR, stateG, stateB;
int toR, toG, toB;

long time;
long lastFade = 0;

int run = 0;

String ledCommand = "";


void reset(){
  Serial.println("system:reset");
  wdt_enable(WDTO_4S);
  
}

 
void setup() {
  
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  digitalWrite(REDPIN, LOW);
  digitalWrite(GREENPIN, LOW);
  digitalWrite(BLUEPIN, LOW);

  stateR = 0;
  stateG = 0;
  stateB = 0;

  toR = 255;
  toG = 255;
  toB = 255;

  ledUpdate();
  
  Serial.begin(9600);
  Serial.setTimeout(25);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
  }
  
}

void ledUpdate() {
  analogWrite(REDPIN, stateR);
  analogWrite(GREENPIN, stateG);  
  analogWrite(BLUEPIN, stateB);
}

void fadeLedColorTo(String color) {
  if( color == "red") {
    if( toR > stateR) stateR += 1;
    else if (toR < stateR ) stateR -= 1;
  }
  else if( color == "green") {
    if( toG > stateG) stateG += 1;
    else if (toG < stateG ) stateG -= 1;
  }
  else if( color == "blue") {
    if( toB > stateB) stateB += 1;
    else if (toB < stateB ) stateB -= 1;
  }
}


 
void loop() {
  time = micros();

  if( Serial.available() > 0) {
    serialInput = Serial.readString();
    if ( serialConnected == false && serialInput == "system:ready" ) {
        serialConnected = true;
        Serial.println("system:connected");
    }
    else if ( serialConnected == true && serialInput == "system:ready" ) {
        serialConnected = true;
        Serial.println("system:stillconnected");
    }
    else if ( serialConnected == true && serialInput == "system:alert:reset" ) {
      reset();
    }
    else if ( serialConnected == true ) {
      if ( serialInput.startsWith("led:") ) {
        serialInput.replace("led:", "");
        if ( serialInput.startsWith("rgb:") ) {
          String values = serialInput;
          values.replace("rgb:", "");
          int red = values.substring(0, 3).toInt();
          int green = values.substring(4, 7).toInt();
          int blue = values.substring(8, 11).toInt();
          toR = red;
          toG = green;
          toB = blue;
          Serial.println(String("led:rgb: " + String(red) + " " + String(green) + " " + String(blue)));
          ledCommand = "fade";
        }
        else if ( serialInput.startsWith("timeout:") ) {
          serialInput.replace("timeout:", "");
          ledTimeout = serialInput.toInt();
          String serialOutput = "";
          serialOutput = String("led:timeout:" + String(ledTimeout));
          Serial.println(serialOutput);
        }
        else if ( serialInput.startsWith("fadein") ) {
          ledCommand = "fade";
          toR = 255;
          toG = 255;
          toB = 255;
          Serial.println("led:fading");          
        }
        else if ( serialInput.startsWith("fadeout") ) {
          toR = 0;
          toG = 0;
          toB = 0;
          ledCommand = "fade";
          Serial.println("led:fading");          
        }
        else if ( serialInput.startsWith("fade") ) {
          ledCommand = "fade";
          Serial.println("led:fading");          
        }
      }
   }
   else return;
  }
  
  if ( time - lastFade >= ledTimeout && ledCommand == "fade" ) {
    if ( toR != stateR || toG != stateG || toB != stateB ) {
      fadeLedColorTo("red");
      fadeLedColorTo("green");
      fadeLedColorTo("blue");
      ledUpdate();
      lastFade = time;
    }
    else {
      ledCommand = "";
      Serial.println("led:finished"); 
    }
  }

  
}
