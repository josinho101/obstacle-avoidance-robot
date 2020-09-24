#include <Servo.h>
#include <AFMotor.h>

#define LOOKOUT_SERVO_PIN 9
#define TOP_SPEED 120
#define TRIG_PIN A4
#define ECHO_PIN A5
#define TURN_RADIUS 750
#define FORWARD_RUNTIME 100

AF_DCMotor motorLeft(1, MOTOR12_64KHZ);
AF_DCMotor motorRight(2, MOTOR12_64KHZ);
Servo lookoutServo;
 
void setup() {  
  initLookoutServo();
  motorLeft.setSpeed(TOP_SPEED);
  motorRight.setSpeed(TOP_SPEED);

  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input
}
 
void loop() { 
  // get obstacle distance at front
  int frontDistance = getObstacleDistance();
  
  // if distance in front of cart is greater than 20cm, then go forward
  if(frontDistance > 20) {
    driveForward(FORWARD_RUNTIME);
  } else {
    // stop the cart
    applyBreak();
    
    // look right and get right obstacle distance
    int rightDistance = getRightDistance();
    // look left and get left obstacle distance
    int leftDistance = getLeftDistance();

    if(rightDistance > leftDistance){
      turnRight(TURN_RADIUS);
    } else {
      turnLeft(TURN_RADIUS);
    }
  }
}

int getObstacleDistance(){
  // Clears the trigPin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);  
  // Calculating the distance. distance = (Speed of sound * duration) / 2
  int distance = duration*0.034/2;
  
  return distance;
}

void initLookoutServo(){
  lookoutServo.attach(LOOKOUT_SERVO_PIN); // attach lookout servo to pin 9
  lookoutServo.write(90); // set lookout servo to angle 0
}

int getRightDistance(){
  for(int angle = 91; angle < 135; angle++)
  {                                  
    lookoutServo.write(angle);
    delay(10);                       
  }

  delay(500);  
  int distance = getObstacleDistance();

  for(int angle = 136; angle >= 90; angle--) 
  {                                
    lookoutServo.write(angle);
    delay(10);                       
  } 

  return distance;
}

int getLeftDistance(){
  for(int angle = 90; angle >= 45; angle--) 
  {                                
    lookoutServo.write(angle);
    delay(10);                       
  } 
  
  delay(500);
  int distance = getObstacleDistance();
  
  for(int angle = 46; angle < 90; angle++)
  {                                  
    lookoutServo.write(angle);
    delay(10);                       
  }

  return distance;
}

void driveForward(int timeDelay) {
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  delay(timeDelay);
}

void driveBackward() {
  motorRight.run(BACKWARD);
  motorLeft.run(BACKWARD);
}

void applyBreak() {
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
}

void turnRight(int timeDelay) {  
  motorRight.run(FORWARD);
  motorLeft.run(BACKWARD);
  delay(timeDelay);
}

void turnLeft(int timeDelay) {  
  motorRight.run(BACKWARD);
  motorLeft.run(FORWARD);
  delay(timeDelay);
}
