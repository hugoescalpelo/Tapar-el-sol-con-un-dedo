void testSequence () {
 //delay (8000);

  //TurHead to the left
  Serial1.println ("Turn head left");
  stopAll ();
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (stepRegistry [LEFT_MOTOR] < TEST_STEPS) {
    runAll ();
  }

  //Turn head to the right
  stopAll ();
  Serial1.println ("Turn head right");
  delay (IBWTT);
  setMotor (LEFT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (stepRegistry [RIGHT_MOTOR] < TEST_STEPS) {
    runAll ();
  }

  //Back to center
  stopAll ();
  Serial1.println ("Turn head center");
  delay (IBWTT);
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (stepRegistry [LEFT_MOTOR] < 0) {
    runAll ();
  }

  //Turn head down
  stopAll ();
  delay (IBWTT);
  Serial1.println ("Turn head down");
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  while (stepRegistry [FRONT_MOTOR] <= TEST_STEPS) {
    runAll ();
  }

  //Turn head up
  stopAll ();
  delay (IBWTT);
  Serial1.println ("Turn head up");
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  while (stepRegistry [REAR_MOTOR] <= TEST_STEPS) {
    runAll ();
  }

  //Center head vertical
  stopAll ();
  Serial1.println (stepRegistry [FRONT_MOTOR]);
  delay (IBWTT);
  Serial1.println ("Turn head center");
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  while (stepRegistry [FRONT_MOTOR] < 0) {
    runAll ();
  }
  Serial1.println (stepRegistry [FRONT_MOTOR]);
  stopAll ();
  delay (IBWTT);
  enableToggle = 1;
}

void setHomeSteps () {
  for (byte i_hs = 0; i_hs > N_MOTORS; i_hs++) {
    stepRegistry [i_hs] = 0;
  }
}

void runUntilCalibrate () {
  bool calibrated = 0;
  while (calibrated == 0) {
    readAbsoluteOrientationSensor ();
    if (buffMag == 3) {
      calibrated = 1;
    }
  }
}

void readAbsoluteOrientationSensor () {
  timeNow = millis ();
  if (timeNow > AOSensorTime) {
    //Get values
    imu::Vector <3> euler = bno.getVector (Adafruit_BNO055::VECTOR_EULER);
    heading = euler.x ();


    //Calibration routine
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration (&system, &gyro, &accel, &mag);

    buffMag = mag;
    //printABSensor ();
    AOSensorTime += BNO055_SAMPLERATE_DELAY_MS;
  }
}

void searchSun () {
  stopSearch = 0;
  reportData = millis ();
  String endd = "end";
  while (stopSearch != 1) {
    readBT ();
    timeNow = millis ();
    if (timeNow > reportData) {
      Serial.print (rValueBT);
      Serial.print (" ");
      Serial.print (reportData);
      Serial.print (" ");
      Serial.println (stopSearch);
      reportData += 2000;
    }
    if (rValueBT.toInt () == -1) {
      stopSearch = 1;
      Serial.println ("Terminador");
    }
    else {
      parsePosition ();
      machinePosition ();
        //Serial.println ("worker");
    }
    //clean ();
  }

}

void parsePosition () {
  lastAz = azimuthSol;
  lastAl = altitudSol;
  byte commaIndex = rValueBT.indexOf (',');
  byte lennngth = rValueBT.length ();
  azimuthSol = rValueBT.substring (0, commaIndex).toFloat ();
  altitudSol = rValueBT.substring (commaIndex + 1, lennngth).toFloat ();
  if (lastAz != azimuthSol || lastAl != altitudSol) {


    Serial.print (azimuthSol);
    Serial.print (" ");
    Serial.println (altitudSol);
    Serial1.println (rValueBT);
    //delay (1000);

  }
}

void machinePosition () {
  //
}

void enableToggleMenu () {
  enableToggle = !enableToggle;
  for (int i_tg = 0; i_tg < N_MOTORS; i_tg++) {
    enableMotor [i_tg] = enableToggle;
  }
  driveAll ();
}

