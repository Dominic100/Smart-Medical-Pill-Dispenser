#include <Stepper.h>
#include <Servo.h>

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define SERVO_PIN 5
const int VACUUM_PIN = 7;

int step_number = 0;
int flag = 1;
const int steps_per_revolution = 512;
Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  servo.attach(SERVO_PIN);
  pinMode(VACUUM_PIN, OUTPUT);
  vacuum_off();
  move(true);
  move(false);
  move(false);
  servo.write(180);
}

void loop() {
  //Serial.println("\nEnter order: ");

  //while(Serial.available()==0) {

  //}
  if(Serial.available()) {

    String target = Serial.readString();
    Serial.println(target);
    if(target!=0) {
      schedule(target);
    }
  }
}

void OneStep(bool dir) {
  if (dir) {
    switch (step_number) {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
    }
  } else {
    switch (step_number) {
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
    }
  }

  step_number = (step_number+1)%4;
}

void schedule(String order) {
  int dir=3;
  /*while(order!=0) {
    int x = order%10;
    for(int i=0; i<x; i++) {
      direction(dir);
    }
    order = order/10;
    dir--;
  }*/
  for(int i=0; i<order.length(); i++) {
    int x = order[i] - '0';
    for(int j=0; j<x; j++) {
      direction(dir);
      delay(5000);
    }
    dir--;
  }
}

void direction(int target_dir) {
  if(target_dir==0) {}
  else if(target_dir==1) {
    move(true);
    delay(2000);
    pick();
    delay(1000);
    move(false);
    delay(2000);
    drop();
  }
  else if(target_dir==2) {
    move(true);
    move(true);
    delay(2000);
    pick();
    delay(1000);
    move(false);
    move(false);
    delay(2000);
    drop();
  }
  else if(target_dir==3) {
    move(false);
    delay(2000);
    pick();
    delay(1000);
    move(true);
    delay(2000);
    drop();
  }
  else {}
}

void move(bool rotation_sense) {
  for (int i = 0; i < steps_per_revolution; i++) {
    OneStep(rotation_sense);
    delay(2);
  }
}

void move_servo(bool rotation_sense) {
  if(rotation_sense) {
    for(int i=180; i>=0; i--) {
      servo.write(i);
      delay(10);
    }
  }
  else {
    for(int i=0; i<=180; i++) {
      servo.write(i);
      delay(10);
    }
  }
  flag = 1-flag;
}

void vacuum_on() {
  digitalWrite(VACUUM_PIN, HIGH);
}

void vacuum_off() {
  digitalWrite(VACUUM_PIN, LOW);
}

void pick() {
  move_servo(flag);
  delay(1000);
  vacuum_on();
  delay(2000);
  move_servo(flag);
}

void drop() {
  move_servo(flag);
  delay(1000);
  vacuum_off();
  delay(2000);
  move_servo(flag);
}
