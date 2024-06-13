#include <Servo.h>
#include <Ultrasonic.h>

// porta princiapal
#define distance 15
int servo1 = 9;
int trigger = 3;
int echo = 2;
int angulo;
int servo_timing = 1000;
bool portaAbrindo = false;
Servo meuServo; 
Ultrasonic u(trigger, echo);

/* Sensor de movimentos */
#define motion 8
#define ledMotion 7

/* Sensor de luminosidade */
#define ldr A0
#define outLeds 50
 
void setup() {
  meuServo.attach(servo1);

  pinMode(motion, INPUT);
  pinMode(ledMotion, OUTPUT);

  pinMode(ldr, INPUT_PULLUP);
  pinMode(outLeds, OUTPUT);

}

// porta princiapal
void portaPrincipal() {
  if (!portaAbrindo) {
    int d = u.read();
    if (d <= distance) {
      // abrir porta principal
      for (angulo = 0; angulo <= 100; angulo++) {
        meuServo.write(angulo); // Define a posição do servo
      }
      portaAbrindo = true;
    }
  } else {
    servo_timing--;
    if (servo_timing <= 0) {
      for (angulo = 100; angulo >= 0; angulo--) {
        meuServo.write(angulo); // Define a posição do servo
      }
      portaAbrindo = false;
      servo_timing = 1000;
    }
  }
}

// sensor de movimentos
void movimentos() {
  int mov = digitalRead(motion);
  digitalWrite(ledMotion, mov);
}

// sensor de luminosidade
void luminosidade() {
  int lum = digitalRead(ldr);
  if (lum >= 100) {
    digitalWrite(outLeds, HIGH);
  } else {
    digitalWrite(outLeds, LOW);
  }
}

// funcao loop
void loop() {
  portaPrincipal();
  movimentos();
  luminosidade();
}