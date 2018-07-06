void gaps ()
{
  Serial1.println  ("Se entro a configuracion de gaps");
  bool gaps_s = 1;
  while (gaps_s != 0)
  {
    leerBT ();
    int buff_g = comandoBT.toInt ();
    switch (buff_g)
    {
      case 320:
        Serial1.println ("320 Ayuda");
        Serial1.println ("321 Gap altitud LV1");
        Serial1.println ("322 Gap azimuth LV1");
        Serial1.println ("323 Gap altitud LV2");
        Serial1.println ("324 Gap azimuth LV2");
        Serial1.println ("325 Gap estabilizador altitud LV1");
        Serial1.println ("325 Gap estabilizador azimuth LV1");
        Serial1.println ("329 Salir");
        comandoBT = 'null';
        break;
      case 321:
        Serial1.println ("Configurar gap altitud lv1");
        setGapAltitudLV1 ();
        Serial1.println ("Configuracion del gap altitud lv1 finalizado");
        comandoBT = 'null';
        break;
      case 322:
        Serial1.println ("Configurar gap azimuth lv1");
        setGapAzimuthLV1 ();
        Serial1.println ("Configuracion del gap azimuth lv1 finalizado");
        comandoBT = 'null';
        break;
      case 323:
        Serial1.println ("Configurar gap altitud lv2");
        setGapAltitudLV2 ();
        Serial1.println ("Configuracion del gap altitud lv2 finalizado");
        comandoBT = 'null';
        break;
      case 324:
        Serial1.println ("Configurar gap azimuth lv2");
        setGapAzimuthLV2 ();
        Serial1.println ("Configuracion del gap azimuth lv2 finalizado");
        comandoBT = 'null';
        break;
      case 325:
        Serial1.println ("Configurar gap estabilizador altitud lv2");
        setGapEstabilizadorAltitudLV1 ();
        Serial1.println ("Configuracion del gap estabilizador altitud lv2 finalizado");
        comandoBT = 'null';
        break;
      case 326:
        Serial1.println ("Configurar gap estabilizador azimuth lv2");
        setGapEstabilizadorAzimuthLV1 ();
        Serial1.println ("Configuracion del gap estabilizador azimuth lv2 finalizado");
        comandoBT = 'null';
        break;
      case 329:
        Serial1.println ("Salir");
        gaps_s = 0;
        comandoBT = 'null';
        break;
      default:
        delay (1000);
        break;
    }
  }
}


void setGapAltitudLV1 ()
{
  Serial1.println ("Se entro a la configuracion del gap altitud lv1");
  comandoBT = 2000;
  bool gal1 = 1;
  while (gal1 != 0)
  {
    leerBT ();

    int buffer_gal1 = comandoBT.toInt ();
    if (buffer_gal1 > 0 && buffer_gal1 < 10)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      gapAltitudLV1 = buffer_gal1;
      gal1 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 0 y menor a 10.");
      delay (1000);
    }
  }
}

void setGapAzimuthLV1 ()
{
  Serial1.println ("Se entro a la configuracion del gap azimuth lv1");
  comandoBT = 2000;
  bool gaz1 = 1;
  while (gaz1 != 0)
  {
    leerBT ();

    int buffer_gaz1 = comandoBT.toInt ();
    if (buffer_gaz1 > 0 && buffer_gaz1 < 10)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      gapAzimuthLV1 = buffer_gaz1;
      gaz1 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 0 y menor a 10.");
      delay (1000);
    }
  }
}

void setGapAltitudLV2 ()
{
  Serial1.println ("Se entro a la configuracion del gap altitud lv2");
  comandoBT = 2000;
  bool gal2 = 1;
  while (gal2 != 0)
  {
    leerBT ();

    int buffer_gal2 = comandoBT.toInt ();
    if (buffer_gal2 > 0 && buffer_gal2 < 10)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      gapAltitudLV2 = buffer_gal2;
      gal2 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 0 y menor a 10.");
      delay (1000);
    }
  }
}

void setGapAzimuthLV2 ()
{
  Serial1.println ("Se entro a la configuracion del gap azimuth lv2");
  comandoBT = 2000;
  bool gaz2 = 1;
  while (gaz2 != 0)
  {
    leerBT ();

    int buffer_gaz2 = comandoBT.toInt ();
    if (buffer_gaz2 > 0 && buffer_gaz2 < 10)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      gapAzimuthLV2 = buffer_gaz2;
      gaz2 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 0 y menor a 10.");
      delay (1000);
    }
  }
}

void setGapEstabilizadorAltitudLV1 ()
{
  Serial1.println ("Se entro a la configuracion de estabilizador de gap altitud lv1");
  comandoBT = 2000;
  bool geal1 = 1;
  while (geal1 != 0)
  {
    leerBT ();

    int buffer_geal1 = comandoBT.toInt ();
    if (buffer_geal1 > 0 && buffer_geal1 < 10)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      estabilizadorAltitudLV1 = buffer_geal1;
      geal1 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 0 y menor a 10.");
      delay (1000);
    }
  }
}

void setGapEstabilizadorAzimuthLV1 ()
{
  Serial1.println ("Se entro a la configuracion de estabilizador de gap azimuth lv1");
  comandoBT = 2000;
  bool geaz1 = 1;
  while (geaz1 != 0)
  {
    leerBT ();

    int buffer_geaz1 = comandoBT.toInt ();
    if (buffer_geaz1 > 0 && buffer_geaz1 < 10)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      estabilizadorAzimuthLV1 = buffer_geaz1;
      geaz1 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 0 y menor a 10.");
      delay (1000);
    }
  }
}
