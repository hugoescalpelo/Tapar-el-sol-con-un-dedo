void setPinModes () {
  for (byte i_pin = 0; i_pin < N_MOTORS; i_pin++) {
    pinMode (PIN [i_pin], OUTPUT);
    pinMode (ENABLE [i_pin], OUTPUT);
    pinMode (DIR [i_pin], OUTPUT);
  }  
}

void setInitials () {
  for (byte i_in = 0; i_in < N_MOTORS; i_in++) {
    digitalWrite (DIR [i_in], LOW);
    digitalWrite (ENABLE [i_in], LOW);
    digitalWrite (PIN [i_in], LOW);
  }
  reportData = millis ();
  setHomeSteps ();
  closeEnoughAz = ON;
  runSample = micros ();
}

