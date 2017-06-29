void RetractCenterLeg()
{
  Serial.println("RetractCenterLeg");
  centerLegMotor->setSpeed(100);
  centerLegMotor->run(BACKWARD);
}

void ExtendCenterLeg()
{
  Serial.println("ExtendCenterLeg");
  centerLegMotor->setSpeed(100);
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

void ListenForSerialInput() {
  int value = Serial.read();
  switch (value) {
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
