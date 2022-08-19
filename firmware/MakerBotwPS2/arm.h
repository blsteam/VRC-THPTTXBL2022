#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define MIN_PWM 0
#define MAX_PWM 4095
#define SERVO_3 4

Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x40);

void setArm(int s3)
{
  char dbg_str[30];
  sprintf(dbg_str,"S3: %d",s3);
  Serial.println(dbg_str);

  pwm3.setPWM(SERVO_3, 0, s3);
}

void initArm()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm3.begin();
  pwm3.setOscillatorFrequency(27000000);
  pwm3.setPWMFreq(50);
  Wire.setClock(400000);

  setArm(0);
}
