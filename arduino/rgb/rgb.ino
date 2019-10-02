 
#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11
 
#define FADESPEED 10 

int pins[3] = {9,10,11};
int index = 0;

int stateRGB[3] = {0, 0, 0};
int toRGB[3] = {0, 0, 0};

long time_stamp;
long last_time_stamp;

long last_fade = 0;
String led_command = "";
double led_timeout = 0;

char array1[3];

char input_byte;
int input_int = 0;
String serial_input = "";


void ledUpdate(int i) {

  
  analogWrite(pins[i], stateRGB[i]);
  
}

void fadeLedColorTo(int i) {
 
   if( toRGB[i] > stateRGB[i] + 4) {
    stateRGB[i] += 4;
    ledUpdate(i);
   }
   else if (toRGB[i] < stateRGB[i] - 4 ) {
    stateRGB[i] -= 4;
    ledUpdate(i);
   }
   else {
    stateRGB[i] = toRGB[i];
    ledUpdate(i);
   }
   
  
}


void setup() {
  
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  digitalWrite(REDPIN, LOW);
  digitalWrite(GREENPIN, LOW);
  digitalWrite(BLUEPIN, LOW);

  analogWrite(BLUEPIN, 0);
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);


  
  // put your setup code here, to run once:
   Serial.begin(115200);
   Serial.println("running...");
   Serial.setTimeout(5);

}



String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}





void loop() {

  
  time_stamp = micros();
  if ( time_stamp < last_time_stamp ) {

    time_stamp = time_stamp + (last_time_stamp - time_stamp);
    
  }
  
  last_time_stamp = time_stamp;



  //////// serial com
  if( Serial.available() > 0) {
    
 
  }

//      for (int i = 0; i < 3; i++) {
//
//          toRGB[i] = Serial.parseInt(); 
//                      
//        }
//      for (int i = 0; i < 3; i++) {
//
//          Serial.println(toRGB[i]); 
//                      
//        }
//      Serial.flush();
      
//     if ( input_byte == '\n' ) {
//      
//      if (serial_input.length() > 0) {
//        
//          //Serial.println(serialInput);
//          ;
//          }
//        
//      for (int i = 0; i < 3; i++) {
//
//            //analogWrite( pins[i], array1[i] );            
//
//            //Serial.println(stateRGB[i]);  
//                       
//        }
//        serial_input = ""; //clears variable for new input
//        input_int = 0;
//        input_byte = 0;
//        index = 0;
//        
//      }
//      
//    
//        
//     else {
//         
//         input_int += input_byte;
//         toRGB[index] = input_int;
//         
//         input_int = 0;
//         index = index + 1;
//         serial_input += input_byte;  //makes the string readString
//        
//      }

        serial_input = Serial.readString();
        if ( serial_input.startsWith("rgb:") || serial_input.startsWith("RGB:") ) {
          
          String values = serial_input;
          values.replace("rgb:", "");
          values.replace("RGB:", "");
          
          int red = getValue(values, (char) ':', 0).toInt();
          int green = getValue(values, (char) ':', 1).toInt();
          int blue = getValue(values, (char) ':', 2).toInt();
          
          toRGB[0] = red;
          toRGB[1] = green;
          toRGB[2] = blue;
          
          
          led_command = "fade";
          
        }



  ///////// fader
      
  if ( time_stamp - last_fade >= led_timeout && led_command == "fade" ) {
    
    if ( toRGB[0] != stateRGB[0] || toRGB[1] != stateRGB[1] || toRGB[2] != stateRGB[2] ) { 
      
      fadeLedColorTo(0);
      fadeLedColorTo(1);
      fadeLedColorTo(2);

      last_fade = time_stamp;
      
      }
      
    else {
      led_command = "";
      }
    }


    
  }
