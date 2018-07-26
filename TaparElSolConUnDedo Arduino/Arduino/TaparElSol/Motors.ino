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

void runAll () {
  timeNow = micros ();
  for (byte i_rn = 0; i_rn > N_MOTORS; i_rn++) {
    if (timeNow >stepTimeTarget [i_rn]  && runMotor [i_rn] && enableMotor [i_rn]) {
      levelMotor [i_rn] = !levelMotor [i_rn];
      stepTimeTarget [i_rn] += stepMotorTime [i_rn];
      if (dirMotor [i_rn]) {
        stepRegistry [i_rn]++;
      }
      else {
        stepRegistry [i_rn]--;
      }
    }
  }
 driveAll ();
}

void driveAll () {
  for (byte i_da = 0; i_da < N_MOTORS; i_da++) {
    digitalWrite (DIR [i_da], dirMotor [i_da]);
    digitalWrite (ENABLE [i_da], enableMotor [i_da]);
    digitalWrite (PIN [i_da], levelMotor [i_da]&runMotor [i_da]);
  }
}

