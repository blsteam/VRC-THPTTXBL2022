#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define MIN_PWM 0
#define MAX_PWM 4095
#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

void setLPWMMotors(int c5, int c6)
{
  char dbg_str[30];
  sprintf(dbg_str,"C5: %d\tC6: %d",c5,c6);
  Serial.println(dbg_str);

  pwm1.setPWM(PWM_CHANNEL5, 0, c5);
  pwm1.setPWM(PWM_CHANNEL6, 0, c6);
}

void initLMotors()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm1.begin();
  pwm1.setOscillatorFrequency(27000000);
  pwm1.setPWMFreq(1600);
  Wire.setClock(400000);

  setLPWMMotors( 0, 0);
}
