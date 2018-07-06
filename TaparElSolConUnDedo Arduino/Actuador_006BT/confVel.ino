void velocidadesBusqueda ()
{
  Serial1.println  ("Se entro a configuracion de velocidades");
  bool vels = 1;
  while (vels != 0)
  {
    leerBT ();
    int buff_v = comandoBT.toInt ();
    switch (buff_v)
    {
      case 320:
        Serial1.println ("330 Ayuda");
        Serial1.println ("331 velocidad x LV1");
        Serial1.println ("332 velocidad y LV1");
        Serial1.println ("333 velocidad x close LV2");
        Serial1.println ("334 velocidad y close LV2");
        Serial1.println ("335 velocidad x far LV2");
        Serial1.println ("336 velocidad y far LV2");
        Serial1.println ("339 Salir");
        comandoBT = 'null';
        break;
      case 321:
        Serial1.println ("Configurar velicidad x lv1");
        setVelXLV1 ();
        Serial1.println ("Configuracion de velocidad x finalziada");
        comandoBT = 'null';
        break;
      case 322:
        Serial1.println ("Configurar velocidad y lv1");
        setVelYLV1 ();
        Serial1.println ("Configuracion de velocidad y lv1 finalziada");
        comandoBT = 'null';
        break;
      case 323:
        Serial1.println ("Configurar velocidad x close lv2");
        setVelXLV2 ();
        Serial1.println ("Configuracion de velocidad x close lv2 finalziada");
        comandoBT = 'null';
        break;
      case 324:
        Serial1.println ("Configurar velocidad y close lv2");
        setVelYLV2 ();
        Serial1.println ("Configuracion de velocidad y close lv2 finalziada");
        comandoBT = 'null';
        break;
      case 325:
        Serial1.println ("Configurar velocidad x far lv2");
        setVelXLV2f ();
        Serial1.println ("Configuracion de velocidad x far lv2 finalziada");
        comandoBT = 'null';
        break;
      case 326:
        Serial1.println ("Configurar velocidad y far lv2");
        setVelYLV2f ();
        Serial1.println ("Configuracion de velocidad y far lv2 finalziada");
        comandoBT = 'null';
        break;
      case 329:
        Serial1.println ("Salir");
        vels = 0;
        comandoBT = 'null';
        break;
      default:
        delay (1000);
        break;
    }
  }
}


void setVelXLV1 ()
{
  Serial1.println ("Se entro a la configuracuion de velocidad x lv1");
  comandoBT = 20000;
  bool velx1 = 1;
  while (velx1 != 0)
  {
    leerBT ();

    int buffer_velx1 = comandoBT.toInt ();
    if (buffer_velx1 > 400 && buffer_velx1 < 10000)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      stepTimeXLV1 = buffer_velx1;
      velx1 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 400 y menor a 10 000");
      delay (1000);
    }
  }
}

void setVelYLV1 ()
{
  Serial1.println ("Se entro a la configuracuion de velocidad y lv1");
  comandoBT = 20000;
  bool vely1 = 1;
  while (vely1 != 0)
  {
    leerBT ();

    int buffer_vely1 = comandoBT.toInt ();
    if (buffer_vely1 > 400 && buffer_vely1 < 10000)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      stepTimeYLV1 = buffer_vely1;
      vely1 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 400 y menor a 10 000");
      delay (1000);
    }
  }
}

void setVelXLV2 ()
{
  Serial1.println ("Se entro a la configuracuion de velocidad x close lv2");
  comandoBT = 20000;
  bool velx2 = 1;
  while (velx2 != 0)
  {
    leerBT ();

    int buffer_velx2 = comandoBT.toInt ();
    if (buffer_velx2 > 400 && buffer_velx2 < 10000)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      stepTimeXLV2_close = buffer_velx2;
      velx2 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 400 y menor a 10 000");
      delay (1000);
    }
  }
}

void setVelYLV2 ()
{
  Serial1.println ("Se entro a la configuracuion de velocidad y close lv2");
  comandoBT = 20000;
  bool vely2 = 1;
  while (vely2 != 0)
  {
    leerBT ();

    int buffer_vely2 = comandoBT.toInt ();
    if (buffer_vely2 > 400 && buffer_vely2 < 10000)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      stepTimeYLV2_close = buffer_vely2;
      vely2 = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 400 y menor a 10 000");
      delay (1000);
    }
  }
}

void setVelXLV2f ()
{
  Serial1.println ("Se entro a la configuracuion de velocidad x far lv2");
  comandoBT = 20000;
  bool velx2f = 1;
  while (velx2f != 0)
  {
    leerBT ();

    int buffer_velx2f = comandoBT.toInt ();
    if (buffer_velx2f > 400 && buffer_velx2f < 10000)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      stepTimeXLV2_far = buffer_velx2f;
      velx2f = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 400 y menor a 10 000");
      delay (1000);
    }
  }
}

void setVelYLV2f ()
{
  Serial1.println ("Se entro a la configuracuion de velocidad y far lv2");
  comandoBT = 20000;
  bool vely2f = 1;
  while (vely2f != 0)
  {
    leerBT ();

    int buffer_vely2f = comandoBT.toInt ();
    if (buffer_vely2f > 400 && buffer_vely2f < 10000000)
    {
      Serial1.print ("Se recibió un ");
      Serial1.println (comandoBT);
      stepTimeYLV2_far = buffer_vely2f;
      vely2f = 0;
    }
    else
    {
      Serial1.print ("Introduzca un numero mayor a 400 y menor a 10 000");
      delay (1000);
    }
  }
}
