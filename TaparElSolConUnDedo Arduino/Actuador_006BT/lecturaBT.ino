void esperarBT ()
{
  while (inicio_bt != 1)
  {
    if (Serial1.available ())
    {
      comandoBT = Serial1.readStringUntil ('\n');
      Serial.println (comandoBT);
      if (comandoBT == "inicio" || comandoBT == "demo")
      {
        inicio_bt = 1;
      }
    }
  }
}

void leerBT ()
{
  if (Serial1.available ())
  {
    comandoBT = Serial1.readStringUntil ('\n');
    Serial.println ();
    Serial.print ("Dato Recibido ");
    Serial.print (comandoBT);
    Serial.println ();
    Serial.println ();
    Serial1.println ();
    Serial1.print ("Dato Recibido ");
    Serial1.print (comandoBT);
    Serial1.println ();
    Serial1.println ();
  }
}
