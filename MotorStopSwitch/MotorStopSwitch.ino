#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield MOTORSHIELD_LOWER = Adafruit_MotorShield();
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *centerLegMotor = MOTORSHIELD_LOWER.getMotor(1);
Adafruit_DCMotor *domeMotor = MOTORSHIELD_LOWER.getMotor(2);
Adafruit_DCMotor *shoulderRightMotor = MOTORSHIELD_LOWER.getMotor(3);
Adafruit_DCMotor *shoulderLeftMotor = MOTORSHIELD_LOWER.getMotor(4);


enum State {
  STOP,
  UP,
  DOWN,
  PARKUP,
  PARKDOWN
} state; // <-- the actual instance, so can't be a typedef

#define UpSwitchPin 0
#define DownSwitchPin 2

void setup() {
  // MotorShield
  MOTORSHIELD_LOWER.begin();  // create with the default frequency 1.6KHz

  pinMode(UpSwitchPin, INPUT_PULLUP);
  pinMode(DownSwitchPin, INPUT_PULLUP);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("MOTOR TEST is ready!");
}

void loop() {
  ListenForSerialInput();
  ListenForCenterEndPointsActive(UpSwitchPin, DownSwitchPin);
  ListenForCenterEndPointsParked(UpSwitchPin, DownSwitchPin);
 
  Serial.print("State:");
  Serial.println(state);
}
