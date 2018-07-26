void beginOrientationSensor () {
  if (!bno.begin ()) {
    Serial.println ("Check Sensor BNO055");
  }
  delay (1000);

  int8_t temp = bno.getTemp ();
  Serial.println ("Temperature ");
  Serial.print (temp);
  Serial.println ("°C");

  bno.setExtCrystalUse (true);
  AOSensorTime = millis () + BNO055_SAMPLERATE_DELAY_MS;

  Serial.println ("Sensor started. Calibrate");
}

