void Log(String from) {
  Serial.print(from);
  Serial.print(":");
  Serial.print(abs(getPotPos(LeftLegPotPin)));
  Serial.print(";");
  Serial.println(abs(getPotPos(RightLegPotPin)));
}
