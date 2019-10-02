
char sinput;
int array1[3];
int index = 0;
String serialInput = "";

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Serial.println("running...");
   Serial.setTimeout(1);

}

void loop() {
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
           //array1[i] = serialInput[i];
           //switchPin(pins[i], serialInput[i]);
            Serial.println(array1[i]);            
            }

          
        }
        
        serialInput = ""; //clears variable for new input
        
        Serial.flush();
      }
      
     else if (sinput == '\r') {
        
        array1[index] = serialInput;
        serialInput = "";
        index = index + 1;
           
        }
        
     else {

          serialInput += sinput;  //makes the string readString
        
      }
     }

  }

}
