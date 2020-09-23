#include <AFMotor.h>
 
AF_DCMotor motor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
 
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motor.setSpeed(200);     // set the speed to 200/255
}
 
void loop() {
  Serial.println("go forward");  
  motor.run(FORWARD);      // spin motor forward
  delay(5000);

  Serial.println("stop");
  motor.run(RELEASE);      // stop motor
  delay(2000);

  Serial.println("go backward"); 
  motor.run(BACKWARD);     // spin motor backward
  delay(5000);
  
  Serial.println("stop");
  motor.run(RELEASE);      // stop motor
  delay(1000);
}
