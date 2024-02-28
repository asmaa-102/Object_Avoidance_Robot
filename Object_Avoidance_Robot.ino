#include <Servo.h>
#include <NewPing.h>
#define in1 7  //Right motor pole 1
#define in2 6  //Right motor pole 2
#define in3 5 //left motor pole 1
#define in4 4  //left motor pole 1
#define ena 9  //Right motor speed
#define enb 10 //Right motor speed

const int trig_pin = 13;//Trigger Pin of Ultrasonic
const int echo_pin = 12;//Echo Pin of Ultrasonic
#define maximum_distance 200
boolean goesForward = false;
int distance = 100;
//Servo servo_motor;  // create servo object to control a servo
//int pos = 0;    // variable to store the servo position

long duration;//used by ultrasonic Function
int distanceRight,distanceLeft;//Cdistance=center Distance Rdistance=Right Distance Ldistance=Left Distance
NewPing sonar(trig_pin, echo_pin, maximum_distance); 
void setup() 
{
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  
    Serial.begin(9600);
  //servo_motor.attach(3);  // attaches the servo on pin 9 to the servo object
  //servo_motor.write(85);  // Initial Pos of Servo at center
  
}


void loop(){
  analogWrite(ena, 150);
  analogWrite(enb, 150);

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  Serial.println(distance);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
   delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}


int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveForward(){

  goesForward=true;

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}

void turnLeft(){

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  delay(500);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  
  
}

void turnRight(){

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(500);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void moveStop(){
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void moveBackward(){

  if(!goesForward){

    goesForward=false;
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
  }
}
