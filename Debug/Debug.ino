/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/


int potpin0 = 0;  // analog pin used to connect the potentiometer
int potpin1 = 1;  // analog pin used to connect the potentiometer
int val0;    // variable to read the value from the analog pin
int val1;    // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);
}

void loop() {
  val0 = analogRead(potpin0);            // reads the value of the potentiometer (value between 0 and 1023)
  val0 = map(val0, 0, 1023, 0, 36);     // scale it to use it with the servo (value between 0 and 180)
  val1 = analogRead(potpin1);            // reads the value of the potentiometer (value between 0 and 1023)
  val1 = map(val1, 0, 1023, 0, 36);     // scale it to use it with the servo (value between 0 and 180)

  Serial.print(val0);
  Serial.print(";");
  Serial.println(val1);
}

