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
      shoulderLeftMotor->setSpeed(0);
      shoulderLeftMotor->run(RELEASE);
      shoulderRightMotor->setSpeed(0);
      shoulderRightMotor->run(RELEASE);
      centerLegMotor->setSpeed(0);
      centerLegMotor->run(RELEASE);
      domeMotor->setSpeed(0);
      domeMotor->run(RELEASE);
      Serial.println("ALL MOTORS STOP");
      break;
  }
}
