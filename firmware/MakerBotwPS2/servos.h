#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define MIN_PWM 0
#define MAX_PWM 4095
#define SERVO_1 3
#define SERVO_2 2

Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x40);

void setRollServos(int s1, int s2)
{
  char dbg_str[30];
  sprintf(dbg_str,"s1: %d\ts2: %d",s1,s2);
  Serial.println(dbg_str);

  pwm4.setPWM(SERVO_1, 0, s1);
  pwm4.setPWM(SERVO_2, 0, s2);
}

void initServos()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm4.begin();
  pwm4.setOscillatorFrequency(27000000);
  pwm4.setPWMFreq(50);
  Wire.setClock(400000);

  setRollServos(0, 0);
}
