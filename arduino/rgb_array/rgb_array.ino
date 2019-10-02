#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11
 
#define FADESPEED 10     // make this higher to slow down

 int pins[3] = {9,10,11};
 int array1[3];

 char sinput;

void setup()
{

  
 Serial.begin(9600);
 Serial.println("running...");
 Serial.setTimeout(1);
 
}

String serialInput = "";


void switchPin(int pin, byte pinnow){
  Serial.println(pinnow);
  if (pinnow == 1) {
    digitalWrite(pin, HIGH);
  }
  else {
    digitalWrite(pin, LOW);
  }
}

void loop()
{
  if( Serial.available() > 0) {
     sinput = Serial.read();
     if (sinput == '\n') {
        //Serial.println(serialInput); //prints string to serial port out
        if (serialInput.length() > 0) {
           Serial.println(serialInput);
           for (int i = 0; i < serialInput.length(); i++) {
           // String inp = String(serialInput[i]);
           // if (inp == "") Serial.print(serialInput[i]);
            array1[i] = serialInput[i];
            //switchPin(pins[i], serialInput[i]);
            }

          
        }
        serialInput = ""; //clears variable for new input
        Serial.flush();
      }
     else {
        serialInput += sinput; //makes the string readString
      }
     }

  }
  

  
