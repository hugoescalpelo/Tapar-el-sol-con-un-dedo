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

void readBT () {
  if (Serial1.available ()) {
    rValueBT = Serial1.readStringUntil ('\n');
    //printReceivedValues ();
  }
}

void clean () {
  rValueBT = 'null';
  buffBT = 200;
}

