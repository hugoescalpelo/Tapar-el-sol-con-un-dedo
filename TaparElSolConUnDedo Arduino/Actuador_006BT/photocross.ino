//Se hacen las lecturas de todas las LDR
void leerPhotocross ()
{
  Serial1.println ("Se entro a la secuencia de lectura de photocross");
  for (int i_phcr = 0; i_phcr < 13; i_phcr++)
  {
    dataPhotocross [i_phcr] = analogRead (photocrossPin [i_phcr]);
  }

  //Evaluar el punto mas brillante en cada eje
  directivaPhotocross [0] = brilloso (dataPhotocross [0], dataPhotocross [1], dataPhotocross [2], dataPhotocross [3], dataPhotocross [4], dataPhotocross [5], dataPhotocross [6]);
  baseX = photoThreshold;
  directivaPhotocross [1] = brilloso (dataPhotocross [7], dataPhotocross [8], dataPhotocross [9], dataPhotocross [3], dataPhotocross [10], dataPhotocross [11], dataPhotocross [12]);
  baseY = photoThreshold;
}

//Devuelve el indice de posición donde impera el brillo de la PhotoCross
int brilloso (int a, int b, int c, int d, int e, int f, int g)
{
  int shiny [] = {a, b, c, d, e, f, g};
  int base = a;
  int indice = 0;
  for ( int iLv2 = 0; iLv2 < 7; iLv2++)
  {
    if (shiny [iLv2] < base)
    {
      base = shiny [iLv2];
      indice = iLv2;
    }
  }
  photoThreshold = base;
  return (indice);
}

void setPhotocrossThreshold ()
{
  Serial1.println ("Se entro a set photocross");
  comandoBT = 2000;
  bool dds = 1;
  while (dds != 0)
  {
    leerBT ();

    int buffer_s = comandoBT.toInt ();
    if (buffer_s > 0 && buffer_s < 1024)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      photoThreshold = buffer_s;
      dds = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 0 y menor a 1024.");
      delay (1000);
    }
  }
}

