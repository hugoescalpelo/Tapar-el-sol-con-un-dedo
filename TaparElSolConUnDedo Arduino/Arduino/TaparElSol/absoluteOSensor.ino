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

void readAbsoluteOrientationSensor () {
  timeNow = millis ();
  if (timeNow > AOSensorTime) {
    imu::Vector <3> euler = bno.getVector (Adafruit_BNO055::VECTOR_EULER);
    heading = euler.x ();
    tilting = euler.y ();


    //Calibration routine
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration (&system, &gyro, &accel, &mag);

    buffMag = mag;
    //printABSensor ();
    AOSensorTime += BNO055_SAMPLERATE_DELAY_MS;
  }
}

