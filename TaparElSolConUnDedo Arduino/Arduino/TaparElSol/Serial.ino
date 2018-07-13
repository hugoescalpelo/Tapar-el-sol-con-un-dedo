void printReceivedValues () {
  Serial.println ();
  Serial.print ("R ");
  Serial.println (rValueBT);
  Serial.println ();

  Serial1.println ();
  Serial.print ("R ");
  Serial.println (rValueBT);
  Serial.println ();
}

void printMenu () {
  Serial.println ();
  Serial.println ("0 menu");
  Serial.println ("1 test");
  Serial.println ("2 calibrate");
  Serial.println ("3 run");
  Serial.println ("4 sensor");
  Serial.println ("5 Tense");
  Serial.println ("6 enable toggle");

  Serial1.println ("0 menu");
  Serial1.println ("1 test");
  Serial1.println ("2 calibriate");
  Serial1.println ("3 run");
  Serial1.println ("4 sensor");
  Serial1.println ("5 tense");
  Serial1.println ("6 enable toggle");
}

