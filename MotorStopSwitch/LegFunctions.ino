void RetractCenterLeg()
{
  Serial.println("RetractCenterLeg");
  centerLegMotor->setSpeed(GlobalMotorSpeed);
  centerLegMotor->run(BACKWARD);
}

void ExtendCenterLeg()
{
  Serial.println("ExtendCenterLeg");
  centerLegMotor->setSpeed(GlobalMotorSpeed);
  centerLegMotor->run(FORWARD);
}

void StopCenterLeg()
{
  Serial.println("StopCenterLeg");
  centerLegMotor->setSpeed(0);
  //centerLegMotor->run(RELEASE);
}

void MoveCenterLeg(int _direction, int _speed) {
  Serial.println("MoveCenterLeg");
  centerLegMotor->setSpeed(_speed);
  centerLegMotor->run(_direction);
}

void LegMode(int legMode)
{
  int rightLegPos;
  int leftLegPos;
  rightLegPos = analogRead(RightLegPotPin);
  rightLegPos = map(rightLegPos, 0, 1023, 0 , 36);

  Serial.println("GOING TO 3 LEGMODE: ");
  shoulderRightMotor->setSpeed(200);


  if (legMode == LEGMODE2) {
    while (rightLegPos > 19) {
      //   LegMode(legMode);
      rightLegPos = analogRead(RightLegPotPin);
      rightLegPos = map(rightLegPos, 0, 1023, 0 , 36);

      leftLegPos = analogRead(LeftLegPotPin);
      leftLegPos = map(leftLegPos, 0, 1023, 0 , 36);

      Serial.println(rightLegPos);

      shoulderRightMotor->run(BACKWARD);
      if (rightLegPos == 19)
      {
        shoulderRightMotor->setSpeed(0);
        //shoulderRightMotor->run(RELEASE);
      }
    }
  }
  if (legMode == LEGMODE3) {
    while (rightLegPos < 36) {
      //   LegMode(legMode);
      rightLegPos = analogRead(RightLegPotPin);
      rightLegPos = map(rightLegPos, 0, 1023, 0 , 36);

      leftLegPos = analogRead(LeftLegPotPin);
      leftLegPos = map(leftLegPos, 0, 1023, 0 , 36);

      Serial.println(rightLegPos);

      shoulderRightMotor->run(FORWARD);
      if (rightLegPos == 36)
      {
        shoulderRightMotor->setSpeed(0);
        //shoulderRightMotor->run(RELEASE);
      }
    }
  }
}

void ListenForSerialInput() {
  int value = Serial.read();
  switch (value) {
    case '3':
      state = LEGMODE3;
      LegMode(LEGMODE3);
      break;
    case '2':
      state = LEGMODE2;
      LegMode(LEGMODE2);
      break;
    case 'd':
      state = DOWN;
      ExtendCenterLeg();
      break;
    case 'u':
      state = UP;
      RetractCenterLeg();
      break;
    case 'C':
      state = STOP;
      StopCenterLeg();
      break;
    case 's':
      state = STOP;
      shoulderRightMotor->setSpeed(0);
      shoulderLeftMotor->setSpeed(0);
      centerLegMotor->setSpeed(0);
      domeMotor->setSpeed(0);
      Serial.println("ALL MOTORS STOP");
      break;
  }
}

void ListenForCenterEndPointsActive(int pin1, int pin2) {

  int UpSwitchPinState = digitalRead(pin1);
  int DownSwitchPinState = digitalRead(pin2);

  state = STOP;
  if (UpSwitchPinState == LOW ) {
    state = PARKUP;
  }
  if (DownSwitchPinState == LOW) {
    state = PARKDOWN;
  }
}

void ListenForCenterEndPointsParked(int pin1, int pin2) {
  if (state == PARKUP && digitalRead(pin1) == LOW)
  {
    ExtendCenterLeg();
    if (digitalRead(pin1) == HIGH)
    {
      StopCenterLeg();
    }
  }
  if (state == PARKDOWN && digitalRead(pin2) == LOW)
  {
    RetractCenterLeg();
    if (digitalRead(pin2) == HIGH)
    {
      StopCenterLeg();
    }
  }
}
