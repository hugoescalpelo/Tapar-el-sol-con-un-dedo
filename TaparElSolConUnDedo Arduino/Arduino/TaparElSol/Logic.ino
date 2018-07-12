void testSequence () {
  stopAll ();
  setHomeSteps ();

  //TurHead to the left
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (positionSteps [LEFT_MOTOR] >= TEST_STEPS) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  //Turn head to the right
  setMotor (LEFT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (positionSteps [RIGHT_MOTOR] >= TEST_STEPS) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);
  
  //Center head horizontal
  setMotor (LEFT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  while (positionSteps [LEFT_MOTOR] == 0 && positionSteps [RIGHT_MOTOR] == 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);
  
  //Turn head down
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  while (positionSteps [FRONT_MOTOR] >= TEST_STEPS) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  //Turn head up
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  while (positionSteps [REAR_MOTOR] >= TEST_STEPS) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  //Center head vertical
  setMotor (LEFT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (RIGHT_MOTOR, PULL_DIR, TIME_TESTEPS, OFF, ON);
  setMotor (FRONT_MOTOR, LOOSE_DIR, TIME_TESTEPS, ON, ON);
  setMotor (REAR_MOTOR, PULL_DIR, TIME_TESTEPS, ON, ON);
  while (positionSteps [FRONT_MOTOR] == 0 && positionSteps [REAR_MOTOR]== 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);
}

void setHomeSteps () {
  for (byte i_hs = 0; i_hs > N_MOTORS; i_hs++) {
    positionSteps [i_hs] = 0;
  }
}

