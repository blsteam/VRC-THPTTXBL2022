  #include <PS2X_lib.h>

  PS2X ps2x; // create PS2 Controller Class object

  #define PS2_DAT 12 // MISO  19
  #define PS2_CMD 13 // MOSI  23
  #define PS2_SEL 15 // SS     5
  #define PS2_CLK 14 // SLK   18

  #define TOP_SPEED 4095
  #define NORM_SPEED 2048
  #define TURNING_FACTOR 1

  #define SINGLE_HAND_DRIVING 0
  #define TWO_HAND_DRIVING 1

  unsigned long int buttonStateGreen = 0, timeRan_Line = 0, valueGreen = 0;
  
  bool driving_mode = TWO_HAND_DRIVING;
  void setupPS2controller()
  {
    int err = -1;
    while (err != 0)
    {
      err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
    }
  }
  bool PS2control()
  {
    int speed = NORM_SPEED;

    if(ps2x.Button(PSB_R2))
    {
      speed = TOP_SPEED;
    }
    if (ps2x.ButtonPressed(PSB_SELECT))
      driving_mode =! driving_mode;

    int nJoyX = 128 - ps2x.Analog(PSS_RX); // read x-joystick
    int nJoyY = 128 - (driving_mode ? ps2x.Analog(PSS_LY) :ps2x.Analog(PSS_RY)); // read y-joystick
    int nMotMixL;                          // Motor (left) mixed output
    int nMotMixR;                          // Motor (right) mixed output


    bool temp = (nJoyY * nJoyX > 0);
    if (nJoyX) // Turning
    {
      nMotMixR = -nJoyX + (nJoyY * temp);
      nMotMixL = nJoyX + (nJoyY * !temp);
    }
    else // Forward or Reverse
    {
      nMotMixL = nJoyY;
      nMotMixR = nJoyY;
    }

    Serial.print(F("Calculated value from joystick: "));
    Serial.print(nMotMixL);
    Serial.print("\t");
    Serial.println(nMotMixR);
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5=0,c6=0,s1=0,s2=0,s3=0;

    if (nMotMixR > 0)
    {
      c3 = nMotMixR;
      c3 = map(c3, 0, 128, 0, speed);
    }

    else if (nMotMixR < 0)
    {
      c4 = abs(nMotMixR) + 1;
      c4 = map(c4, 0, 128, 0, speed);
    }

    if (nMotMixL > 0)
    {
      c1 = nMotMixL;
      c1 = map(c1, 0, 128, 0, speed);
    }
    else if (nMotMixL < 0)
    {
      c2 = abs(nMotMixL)+1;
      c2 = map(c2, 0, 128, 0, speed);
    }

  if (ps2x.Button(PSB_L1))
  {
    c5 = ps2x.Analog(PSB_L1);
    c5 = TOP_SPEED;
  }
  else if (ps2x.Button(PSB_L2))
  {
    c6 = ps2x.Analog(PSB_L2);
    c6 = TOP_SPEED;
  }

  if (ps2x.Button(PSB_PAD_UP))
  {
    for (uint16_t i = 0; i < 4096; i += 8)
    {
      s1 = ps2x.Analog(PSB_PAD_UP);
      s1 = 105;
      s2 = ps2x.Analog(PSB_PAD_UP);
      s2 = 105;
    }
  }
  else if (ps2x.Button(PSB_R1))
  {
    for(uint16_t i = 0; i < 4096; i+=8)
    {
      s3 = ps2x.Analog(PSB_R1);
      s3 = 105;
    }
  }
  setPWMMotors(c1,c2,c3,c4);
  setLPWMMotors(c5,c6);
  setRollServos(s1,s2);
  setArm(s3);
  }

  
