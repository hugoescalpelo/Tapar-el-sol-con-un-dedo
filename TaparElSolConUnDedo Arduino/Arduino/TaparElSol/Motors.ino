void setMotor (byte nMotor, bool bDir, long tStep, bool activeMotor) {
  dirMotor [nMotor] = bDir;
  stepMotorTime [nMotor] = tStep;
  runMotor [nMotor] = activeMotor;
  stepTimeTarget [nMotor] = tStep + micros ();
}

