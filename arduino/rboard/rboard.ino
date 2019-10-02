// int pin1 = 5;
// int pin2 = 2;
// int pin3 = 3;
// int pin4 = 4;

 int pins[4] = {4,5,6,9};

 char sinput;

void setup()
{
 Serial.begin(9600);
 Serial.println("running...");
 Serial.setTimeout(2);
 
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(6, OUTPUT);
 delay(200);
 digitalWrite(2, HIGH);
 digitalWrite(5, HIGH);
 digitalWrite(4, HIGH);
 digitalWrite(9, LOW);
 digitalWrite(6, HIGH);
 delay(200);
 digitalWrite(2, LOW);
 digitalWrite(5, LOW);
 digitalWrite(4, LOW);
 digitalWrite(9, HIGH);
 digitalWrite(6, LOW);
 delay(200);
 digitalWrite(2, HIGH);
 digitalWrite(5, HIGH);
 digitalWrite(4, HIGH);
 digitalWrite(9, LOW);
 digitalWrite(6, HIGH);
 delay(200);
  digitalWrite(2, LOW);
 digitalWrite(5, LOW);
 digitalWrite(4, LOW);
 digitalWrite(9, HIGH);
 digitalWrite(6, LOW);
 delay(200);
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
        if (serialInput.length() >= 4) {
           for (int i = 0; i < serialInput.length(); i++) {
           // String inp = String(serialInput[i]);
           // if (inp == "") Serial.print(serialInput[i]);
            
            if ( i == 1 ) {
              switchPin(pins[i], serialInput[0]);
            }
            else {
              switchPin(pins[i], serialInput[i]);
            }

           }
          
        }
        serialInput = ""; //clears variable for new input
        Serial.flush();
      }
     else {
        serialInput += sinput; //makes the string readString
      }
     }
     //Serial.print(pins[0]);
     //Serial.print(pins[1]);
     //Serial.print(pins[2]);
     //Serial.println(pins[3]);
      
  }
  

  
