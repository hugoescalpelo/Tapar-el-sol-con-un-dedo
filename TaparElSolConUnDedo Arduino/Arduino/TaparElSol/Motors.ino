void setMotor (byte nMotor, bool bDir, long tStep, bool activeMotor, bool enMotor) {
  dirMotor [nMotor] = bDir;
  stepMotorTime [nMotor] = tStep;
  runMotor [nMotor] = activeMotor;
  stepTimeTarget [nMotor] = tStep + micros ();
  enableMotor [nMotor] = enMotor;
}

void stopAll () {
  runMotor [LEFT_MOTOR] = OFF;
  runMotor [RIGHT_MOTOR] = OFF;
  runMotor [FRONT_MOTOR] = OFF;
  runMotor [REAR_MOTOR] = OFF;
}

void runAllTest () {
  timeNow = micros ();
  for (byte i_rn = 0; i_rn > N_MOTORS; i_rn++) {
    if (timeNow >stepTimeTarget [i_rn]  && runMotor [i_rn]) {
      levelMotor [i_rn] = !levelMotor [i_rn];
      stepTimeTarget [i_rn] += stepMotorTime [i_rn];
      if (dirMotor [i_rn]) {
        positionSteps [i_rn]++;
      }
      else {
        positionSteps [i_rn]--;
      }
    }
  }

}

