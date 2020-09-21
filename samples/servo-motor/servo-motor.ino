#include <Servo.h>
 
Servo servo1;
                
int angle = 0;    

void setup() {
  servo1.attach(9); // attach the signal pin of servo to pin 9 of arduino
}

void loop() 
{ 
  for(angle = 0; angle < 180; angle++) // command to move from 0 degrees to 180 degrees 
  {                                  
    servo1.write(angle); //command to rotate the servo to the specified angle
    delay(10);                       
  } 
 
  delay(1000);
  
  for(angle = 180; angle>=1; angle--) // command to move from 180 degrees to 0 degrees 
  {                                
    servo1.write(angle); //command to rotate the servo to the specified angle
    delay(10);                       
  } 

  delay(2000);
}
