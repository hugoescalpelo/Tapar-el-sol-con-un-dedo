void waitHandShake () {
  bool handShake = 0;
  while (handShake == 0) {
    readBT ();
    buffBT = rValueBT.toInt ();
    if (buffBT == HANDSHAKE_CODE) {
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

void waitTest () {
  bool test = 0;
  while (test == 0) {
    readBT ();
    if (rValueBT == "test") {
      testSequence ();
      clean ();
    }
  }
}

void clean () {
  rValueBT = 'null';
  buffBT = 200;
}

