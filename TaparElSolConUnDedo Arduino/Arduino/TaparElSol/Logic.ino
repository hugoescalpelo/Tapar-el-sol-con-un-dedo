void testSequence () {
  stopAll ();
  setHomeSteps ();

  //TurHead to the left
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (stepRegistry [LEFT_MOTOR] < TEST_STEPS) {
    runAll ();
  }
  stopAll ();
  delay (IBWTT);

  //Turn head to the right
  setMotor (LEFT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (stepRegistry [RIGHT_MOTOR] < TEST_STEPS) {
    runAll ();
  }
  stopAll ();
  delay (IBWTT);

  //Center head horizontal
  setMotor (LEFT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (stepRegistry [LEFT_MOTOR] == 0 && stepRegistry [RIGHT_MOTOR] == 0) {
    runAll ();
  }
  stopAll ();
  delay (IBWTT);

  //Turn head down
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  while (stepRegistry [FRONT_MOTOR] <= TEST_STEPS) {
    runAll ();
  }
  stopAll ();
  delay (IBWTT);

  //Turn head up
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  while (stepRegistry [REAR_MOTOR] <= TEST_STEPS) {
    runAll ();
  }
  stopAll ();
  delay (IBWTT);

  //Center head vertical
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  while (stepRegistry [FRONT_MOTOR] == 0 && stepRegistry [REAR_MOTOR] == 0) {
    runAll ();
  }
  stopAll ();
  delay (IBWTT);
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
  bool stopSearch = 0;
  while (stopSearch == 0) {
    readBT ();
    if (rValueBT == "end") {
      stopSearch = 1;
    }
    else {
      parsePosition ();
      machinePosition ();
    }
  }

}

void parsePosition () {
  if (rValueBT != 'null') {
    byte commaIndex = rValueBT.indexOf (',');
    byte lennngth = rValueBT.length ();
    azimuthSol = rValueBT.substring (0, commaIndex).toFloat ();
    altitudSol = rValueBT.substring (commaIndex + 1, lennngth).toFloat ();
  }
}

void machinePosition () {
  //
}

