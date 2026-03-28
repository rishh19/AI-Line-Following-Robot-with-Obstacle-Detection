#define enA 10
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enB 5

#define L_S A0
#define R_S A1

#define echo A2
#define trigger A3

#define servo A5

int Set = 25;   // obstacle detection distance
int distance_L, distance_F, distance_R; 

int speedF = 70;   // forward speed
int speedT = 55;   // turning speed

void setup(){

  Serial.begin(9600);

  pinMode(R_S, INPUT);  
  pinMode(L_S, INPUT);

  pinMode(echo, INPUT );
  pinMode(trigger, OUTPUT);

  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT);   
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT); 

  pinMode(servo, OUTPUT);

  // Servo sweep
  for (int angle = 70; angle <= 140; angle += 5)
    servoPulse(servo, angle);

  for (int angle = 140; angle >= 0; angle -= 5)
    servoPulse(servo, angle);

  for (int angle = 0; angle <= 70; angle += 5)
    servoPulse(servo, angle);

  distance_F = Ultrasonic_read();
  delay(500);
}

void loop(){  

  distance_F = Ultrasonic_read();
  Serial.print("D F=");
  Serial.println(distance_F);

  // OBSTACLE DETECTION + BRAKE
  if(distance_F <= Set){
    suddenBrake();
    Check_side();
    return;
  }

  // LINE FOLLOWING
  if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){
    analogWrite(enA, speedF);
    analogWrite(enB, speedF);
    forword();
  }
  else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){
    Stop(); 
  }
  else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){
    analogWrite(enA, speedT);
    analogWrite(enB, speedT);
    turnRight();
  }
  else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){
    analogWrite(enA, speedT);
    analogWrite(enB, speedT);
    turnLeft();
  }

  delay(10);
}

// SUDDEN BRAKE
void suddenBrake(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(100);

  Stop();
  delay(100);
}

// FIND LINE AGAIN
void findLine(){
  analogWrite(enA, 60);
  analogWrite(enB, 60);

  while(true){

    if((digitalRead(L_S) == 0) || (digitalRead(R_S) == 0)){
      Stop();
      delay(100);
      break;
    }

    // small zig-zag search
    turnRight();
    delay(50);

    turnLeft();
    delay(50);
  }
}

// Servo control
void servoPulse (int pin, int angle){
  int pwm = (angle * 11) + 500;      
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(40);
}

// Ultrasonic
long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}

//DECIDE DIRECTION + RETURN TO LINE
void compareDistance(){
  if(distance_L > distance_R){
    turnLeft();
    delay(400);

    forword();
    delay(300);

    findLine();   //return to line
  }
  else{
    turnRight();
    delay(400);

    forword();
    delay(300);

    findLine();   //return to line
  }
}

// Check both sides
void Check_side(){
  Stop();
  delay(200);

  // right scan
  for (int angle = 70; angle <= 140; angle += 5)
    servoPulse(servo, angle);

  delay(200);
  distance_R = Ultrasonic_read();
  Serial.print("D R=");
  Serial.println(distance_R);

  // left scan
  for (int angle = 140; angle >= 0; angle -= 5)
    servoPulse(servo, angle);

  delay(300);
  distance_L = Ultrasonic_read();
  Serial.print("D L=");
  Serial.println(distance_L);

  // center
  for (int angle = 0; angle <= 70; angle += 5)
    servoPulse(servo, angle);

  delay(200);

  compareDistance();
}

// Motor controls
void forword(){  
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);  
}

void backword(){ 
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);  
}

void turnRight(){ 
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);  
}

void turnLeft(){ 
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);  
}

void Stop(){ 
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, LOW);  
}