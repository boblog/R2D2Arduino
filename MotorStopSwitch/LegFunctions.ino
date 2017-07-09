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

void StopShoulderMotors(bool released) {
  Log("STOPPING after going into 3 LegMode");
  
  shoulderLeftMotor->setSpeed(0);
  if (released)
    shoulderLeftMotor->run(RELEASE);
  
  shoulderRightMotor->setSpeed(0);
  if (released)
    shoulderRightMotor->run(RELEASE);
}

void LegMode(int legMode)
{
  shoulderLeftMotor->setSpeed(GlobalLegSpeed);
  shoulderRightMotor->setSpeed(GlobalLegSpeed);

  if (legMode == LEGMODE3) {
    while ( (abs(getPotPos(LeftLegPotPin) > Left3LegModePotValue)) || (abs(getPotPos(RightLegPotPin) > Right3LegModePotValue)) ) {
      Log("Going into 3 LegMode");
      shoulderLeftMotor->run(BACKWARD);
      shoulderRightMotor->run(BACKWARD);
    };
  }
  if (legMode == LEGMODE2) {
    while ( (abs(getPotPos(LeftLegPotPin) < Left2LegModePotValue)) || (abs(getPotPos(RightLegPotPin) < Right2LegModePotValue)) ) {
      Log("Going into 2 LegMode");
      shoulderLeftMotor->run(FORWARD);
      shoulderRightMotor->run(FORWARD);
    };
  }
  StopShoulderMotors(false);
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



int getPotPos(int pot) {
  int val = abs(analogRead(pot));
  val = map(val, 0, 1023, 0 , 36);
  return val;
}
