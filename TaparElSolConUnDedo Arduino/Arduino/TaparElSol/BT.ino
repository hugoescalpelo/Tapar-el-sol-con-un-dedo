void waitHandShake () {
  bool handShake = 0;
  while (handShake == 0) {
    readBT ();
    buffBT = rValueBT.toInt ();
    if (buffBT == HANDSHAKE_CODE) {
      //testSequence ();
      handShake = 1;
    }    
  }
}

void readBT () {
  if (Serial1.available ()) {
    rValueBT = Serial1.readStringUntil ('\n');
    //printReceivedValues ();
  }
}

