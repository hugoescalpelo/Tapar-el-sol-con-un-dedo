//Wait for a message that is the same as the hardcoded, this is like
//an authentication step
void waitHandShake () {
  bool handShake = 0;
  while (handShake == 0) {
    readBT ();
    buffBT = rValueBT.toInt ();
    if (buffBT == HANDSHAKE_CODE) {
      Serial1.println ("Welcome");
      handShake = 1;
      clean ();
    }    
  }
}

//Standart lecture procedure, used all across the program
void readBT () {
  if (Serial1.available ()) {
    rValueBT = Serial1.readStringUntil ('\n');
    //printReceivedValues ();
  }
}

//Ceaning sequence for rValueBT and BuffBT, this is needed to prevent
//reenter to instructions already selected
void clean () {
  rValueBT = 'null';
  buffBT = 200;
}

