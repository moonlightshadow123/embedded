#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo1;
Servo servo2;

String cmd;
char cmd_char;

void forward(){
  motor1.setSpeed(225);
  motor2.setSpeed(225);
  motor3.setSpeed(225);
  motor4.setSpeed(225);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void backward(){
  motor1.setSpeed(225);
  motor2.setSpeed(225);
  motor3.setSpeed(225);
  motor4.setSpeed(225);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void left_move(){
  motor1.setSpeed(225);
  motor2.setSpeed(225);
  motor3.setSpeed(225);
  motor4.setSpeed(225);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void right_move(){
  motor1.setSpeed(225);
  motor2.setSpeed(225);
  motor3.setSpeed(225);
  motor4.setSpeed(225);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void left_turn(){
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(100);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void right_turn(){
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(100);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void stop_motor(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  servo1.attach(10);
  servo2.attach(9);
}

void s1_0(){
  int val = servo1.read();
  servo1.write(40);
  delay(200);
  servo1.write(val);
  Serial.println(val);
}

void s1_180(){
  int val = servo1.read();
  servo1.write(140);
  delay(200);
  servo1.write(val);
  Serial.println(val);
}

void s2_0(){
  int value = servo2.read();
  servo2.write(value-40);
  delay(100);
  //servo2.write(val);
  Serial.println(value);
}

void s2_180(){
  int value = servo2.read();
  servo2.write(value+40);
  delay(100);
  //servo2.write(val);
  Serial.println(value);
}

void loop() {
  // put your main code here, to run repeatedly:
  //forward();
  if(Serial.available()>0){
    cmd_char = Serial.read();
    /*cmd = Serial.readString();
    //cmd.remove(cmd.length()-1);
    Serial.println(cmd);
    Serial.println(cmd.length());
    String a = String("forward");
    Serial.println(a.equals("forward"));
    Serial.println(cmd.equals("forward"));
    Serial.println(a.length());*/
    Serial.println(cmd_char);
    if(cmd_char == 'U'){
      forward();
      Serial.println("Hey Forward!");
    }else if(cmd_char == 'D'){
      backward();
    }else if(cmd_char == 'L'){
      left_move();
    }else if(cmd_char == 'R'){
      right_move();
    }else if(cmd_char == 'X'){
      left_turn();
    }else if(cmd_char == 'B'){
      right_turn();
    }else if(cmd_char == 'A'){
      stop_motor();
    }else if(cmd_char == 'E'){
      s1_0();
    }else if(cmd_char == 'F'){
      s1_180();
    }else if(cmd_char == 'G'){
      s2_0();
    }else if(cmd_char == 'H'){
      s2_180();
    }
  }
}
