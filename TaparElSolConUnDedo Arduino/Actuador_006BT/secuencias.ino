void callDemo ()//Llamar demo
{
  Serial1.println ("Se entro al demo");
  //Leer brujula
  compass.read ();//Leer brujula
  headingF = compass.heading ();//Direccion de la cabeza

  //Leer acelerometro
  adxl.readAccel(&x, &y, &z);//Leer acelerometro
  aL = altitudF ();//Calcular altitud del brazo-cabeza-dedo

  //Llenar anillos de promediado para funcionamiento inmediato
  for (i_resolver = 0; i_resolver < MUESTRAS; i_resolver++)
  {
    promedioHeading [i_resolver] = headingF;
    promedioAltitud [i_resolver] = aL;
  }

  //Leer photocross
  leerPhotocross ();

  //Tensar 
  tensar ();

  //Leer sensores de limite
  leerLimites ();

  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//yaw+
  {
    paso (motorXder, tiempoPasoDemo, pasoDemo, 1);
  }
  delay (tDemo);
  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//yaw-
  {
    paso (motorXizq, tiempoPasoDemo, pasoDemo, 1);
  }
  delay (tDemo);
  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//yaw-
  {
    paso (motorXizq, tiempoPasoDemo, pasoDemo, 1);
  }
  delay (tDemo);
  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//yaw+
  {
    paso (motorXder, tiempoPasoDemo, pasoDemo, 1);
  }
  delay (tDemo);

  delay (tDemo);

  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//pitch+
  {
    paso (motorYarr, tiempoPasoDemo, pasoDemo, 1);
  }
  delay (tDemo);
  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//pitch-
  {
    paso (motorYabj, tiempoPasoDemo, pasoDemo, 1);
  }
  delay (tDemo);
  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//pitch-
  {
    paso (motorYabj, tiempoPasoDemo, pasoDemo, 1);
  }
  delay (tDemo);
  for (int i_demo = 0; i_demo < avanceDemo; i_demo++)//pitch+
  {
    paso (motorYarr, tiempoPasoDemo, pasoDemo, 1);
  }


  imprimirSensores ();
  imprimirPhotocross ();
  imprimirLimites ();
}

float altitudF ()//Calcular angulo de altitud
{
  //  if (x > 4000)//Artilugio para corregir desborde
  //  {
  //    x = 65535 - x;//Angulo circular
  //    negX = 1;//Bandera que hereda el signo
  //  }
  //  else
  //  {
  //    negX = 0;//Bandera que hereda el signo
  //  }
  //
  //  if (y > 4000)//Artilugio para corregir desborde
  //  {
  //    y = 65535 - y;//Angulo circular
  //    negY = 1;//Bandera que hereda el signo
  //  }
  //  else
  //  {
  //    negY = 0;//Bandera que hereda el signo
  //  }
  //
  //  //OBTENER ANGULO COMPENSADO EN TILT
  //  float ang_lev = atan2 (y, x) * 100;//angulo de gravedad
  //  ang_lev = mapf (ang_lev, 0, 90, 0, 55);//Ampliar rango

  float ang_lev = 360 - abs (atan2 (compass.a.y, compass.a.z) * 100);
  ang_lev = mapf (ang_lev, 50, 200, 0, 90);
  return (ang_lev);//Enviar angulo
}

void imprimirPhotocross ()
{
  Serial1.print ("dX ");
  Serial1.print (directivaPhotocross [0]);
  Serial1.print (" bX ");
  Serial1.print (baseX);
  Serial1.print (" dY ");
  Serial1.print (directivaPhotocross [1]);
  Serial1.print (" bY ");
  Serial1.print (baseY);
  Serial1.println ();
}

void imprimirSensores ()
{
  //Enviar datos
  Serial1.print ("hF ");
  Serial1.print (headingF);
  Serial1.print (" aL ");
  Serial1.print (aL);
  Serial1.println ();
}

void imprimirLimites ()
{
  Serial1.print ("xIz ");
  Serial1.print (datoLimXizq);
  Serial1.print (" xDe ");
  Serial1.print (datoLimXder);
  Serial1.print (" yAr ");
  Serial1.print (datoLimYarriba);
  Serial1.print (" yAb ");
  Serial1.print (datoLimYabajo);

  Serial1.println ();
}
void brAccel ()
{
  Serial1.println ("Se entro a la lectura de brujula acelerometro");
  //Leer brujula
  compass.read ();//Leer brujula
  headingF = compass.heading ();//Direccion de la cabeza

  //Leer acelerometro
  adxl.readAccel(&x, &y, &z);//Leer acelerometro
  aL = altitudF ();//Calcular altitud del brazo-cabeza-dedo

  imprimirSensores ();
}

void leerLimites ()
{
  datoLimXizq = digitalRead (pinLimXizq);
  datoLimXder = digitalRead (pinLimXder);
  datoLimYarriba = digitalRead (pinLimYarriba);
  datoLimYabajo = digitalRead (pinLimYabajo);
}

