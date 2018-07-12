void setPinModes () {
  for (byte i_pin = 0; i_pin < N_MOTORS; i_pin++) {
    pinMode (PIN [i_pin], OUTPUT);
    pinMode (ENABLE [i_pin], OUTPUT);
    pinMode (DIR [i_pin], OUTPUT);
  }  
}

