void funcionar ()
{
  Serial1.println ("Se entro al menu de funcionamiento");
  bool fn_b = 1;
  while (fn_b != 0)
  {
    leerBT ();
    int funcionarCom = comandoBT.toInt ();
    switch (funcionarCom)
    {
      case 30:
        Serial1.println ("30 Ayuda");
        Serial1.println ("31 Funcionar");
        Serial1.println ("32 Configurar Gaps");
        Serial1.println ("33 Configurar velocidades de busqueda");
        Serial1.println ("34 Configurar automaticos");
        Serial1.println ("39 Salir");
        comandoBT = 'null';
        break;
      case 31:
        Serial1.println ("Funcionar funcionar");
        actualizarPosicion ();
        Serial1.println ("funcionamiento finalizado");
        comandoBT = 'null';
        break;
      case 32:
        Serial1.println ("Configuracion de gaps");
        gaps ();
        Serial1.println ("Configuracion de gaps finalizada");
        comandoBT = 'null';
        break;
      case 33:
        Serial1.println ("Configuracion de velocidades de busqueda");
        velocidadesBusqueda ();
        Serial1.println ("Configuracion de velocidades de busqueda finalziado");
        comandoBT = 'null';
        break;
      case 34:
        Serial1.println ("Configuracion de automaticos");
        automaticos ();
        Serial1.println ("Configuracion de automaticos finalizada");
        comandoBT = 'null';
        break;
      case 39:
        comandoBT = 'null';
        fn_b = 0;
        Serial1.println ("Salir");
        break;
      default:
        //Default
        break;
    }
  }
}

void actualizarPosicion ()
{
  Serial1.println ("Se entro a actualizar Posicion");
  bool closeEnough = 1;
  comandoBT = "0";
  while (closeEnough != 0)
  {
    leerBT ();
    if (comandoBT != "0")
    {
      funcionarCom = comandoBT.length ();
      if (premisaLV = 1)
      {
        if (funcionarCom == 1)
        {
          if (comandoBT = "a")
          {
            closeEnough = 0;
            Serial1.println ("Instruccion fin detectada");
          }
        }
        if (funcionarCom == 11)
        {
          Serial1.println ("Se entro al seguidor");
          Serial1.println();
          Serial1.println();
          Serial1.println();
          posicionSol ();
          posicionLocal ();
          diferencias ();
          motoDiferenciasLV1();
          cerrarDiferencias ();
          Serial1.print ("fAz ");
          Serial1.print (flagAzimuthLV1);
          Serial1.print (" fAl ");
          Serial1.println (flagAltitudLV1);

          //Para ir a lv2 cambioLV debe estar en modo automatico (1)
        }
        if (flagAzimuthLV1 == 1 && flagAltitudLV1 == 1)
        {
          //tensar2 ();
          if (cambioLv == 1)
          {
            closeEnough = 0;
            Serial1.println ("Se cumplio el close enough");
            Serial1.println();
            Serial1.println();
            Serial1.println();
            premisaLV = 2;
          }
        }
        if (premisaLV == 2)
        {
          if (closeEnough == 0 && cambioLv == 1)//Suficientemente cerca y cambio automatico activado
          {
            Serial1.println ("Se entro a LV2");
            actualizarPosicionLV2 ();
            Serial1.println ("Se salio de lv2");
          }
        }
      }
      else if (funcionarCom == 3)
      {
        if (comandoBT == "310")
        {
          Serial1.println ("Angulo azimuth,altitud de la forma xxx.x,xxx.x");
          Serial1.println ("310 Ayuda");
          Serial1.println ("311 Forzar LV2");
          Serial1.println ("312 Leer brujula acelerometro");
          Serial1.println ("313 Sostener/soltar");
          Serial1.println ("319 Detener");
          comandoBT = "0";
        }
        else if (comandoBT == "311")
        {
          Serial1.println ("Funcionando");
          actualizarPosicionLV2 ();
          Serial1.println ("Detenido");
          comandoBT = "0";
        }
        else if (comandoBT == "312")
        {
          Serial1.println ("Lectura de la brujula acelerometro");
          brAccel ();
          Serial1.println ("Lectura finalizada");
          comandoBT = "0";
        }
        else if (comandoBT == "313")
        {
          Serial1.println ("Sostener/soltar");
          sostenerSoltar ();
          Serial1.println ("Sostener/Soltar finalizado");
          comandoBT = "0";
        }
        else if (comandoBT == "319")
        {
          comandoBT = "0";
          closeEnough = 0;
          Serial1.println ("Salir");
        }
      }
      //comandoBT = "0";
    }
  }

}

void posicionSol ()
{
  String buffAzimuthSol = comandoBT.substring (0, 5);
  float buffDatoAzimuthSol = buffAzimuthSol.toFloat ();
  azimuthSol = buffDatoAzimuthSol;

  String buffAltitudSol = comandoBT.substring (6, 11);
  float buffDatoAltitudSol = buffAltitudSol.toFloat ();
  altitudSol = buffDatoAltitudSol;

  //  Serial1.println ("Strings");
  //  Serial1.print (buffAzimuthSol);
  //  Serial1.print (" ");
  //  Serial1.println (buffAltitudSol);

  Serial1.println ("Recibidor de posicion de sol");
  Serial1.print ("az ");
  Serial1.print (azimuthSol);
  Serial1.print (" al ");
  Serial1.println (altitudSol);
}

void posicionLocal ()
{
  Serial1.println ("Calculador de posicion local");
  if (lecturaSensores == 1)
  {
    //Leer promediado
    compass.read ();
    promedioHeading [i_promediar] = compass.heading ();
    //adxl.readAccel (&x, &y, &z);
    promedioAltitud [i_promediar] = altitudF ();
    i_promediar++;
    i_promediar = i_promediar % MUESTRAS;
    int headingMientras = 0;
    int altitudMientras = 0;
    for (i_resolver = 0; i_resolver < MUESTRAS; i_resolver++)
    {
      headingMientras += promedioHeading [i_resolver];
      altitudMientras += promedioAltitud [i_resolver];
    }
    headingF = headingMientras / MUESTRAS;
    aL = altitudMientras / MUESTRAS;

    //Leer sensores de limite
    datoLimXizq = digitalRead (pinLimXizq);
    datoLimXder = digitalRead (pinLimXder);
    datoLimYarriba = digitalRead (pinLimYarriba);
    datoLimYabajo = digitalRead (pinLimYabajo);

    imprimirSensores ();
    //imprimirLimites ();
  }
  else
  {
    //lectura cruda

    //Leer brujula
    compass.read ();//Leer brujula
    headingF = compass.heading ();//Direccion de la cabeza
    //Leer acelerometro
    adxl.readAccel(&x, &y, &z);//Leer acelerometro
    aL = altitudF ();//Calcular altitud del brazo-cabeza-dedoa

    //Leer sensores de limite
    datoLimXizq = digitalRead (pinLimXizq);
    datoLimXder = digitalRead (pinLimXder);
    datoLimYarriba = digitalRead (pinLimYarriba);
    datoLimYabajo = digitalRead (pinLimYabajo);

    imprimirSensores ();
    //imprimirLimites ();
  }
}

void diferencias ()
{
  diferenciaAzimuth = headingF - azimuthSol;
  diferenciaAzimuthAbs = abs (diferenciaAzimuth);
  diferenciaAltitud = aL - altitudSol;
  diferenciaAltitudAbs = abs (diferenciaAltitud);

  //  Serial1.println ("Se entro a diferencias");
  //  Serial1.print ("d az ");
  //  Serial1.print (diferenciaAzimuth);
  //  Serial1.print (" d al ");
  //  Serial1.println (diferenciaAltitud);
}

void motoDiferenciasLV1 ()
{
  if (diferenciaAzimuth >= 180)
  {
    if (diferenciaAzimuth >= 0)
    {
      motorActuar [i_azimuth] = motorXizq;
    }
    else
    {
      motorActuar [i_azimuth] = motorXder;
    }
  }
  else
  {
    if (diferenciaAzimuth >= 0)
    {
      motorActuar [i_azimuth] = motorXder;
    }
    else
    {
      motorActuar [i_azimuth] = motorXizq;
    }
  }
  if (diferenciaAltitudAbs >= 180)
  {
    if (diferenciaAltitud >= 0)
    {
      motorActuar [i_altitud] = motorYarr;
    }
    else
    {
      motorActuar [i_altitud] = motorYabj;
    }
  }
  else
  {
    if (diferenciaAltitud >= 0)
    {
      motorActuar [i_altitud] = motorYabj;
    }
    else
    {
      motorActuar [i_altitud] = motorYarr;
    }
  }
}

void cerrarDiferencias ()
{
  if (diferenciaAzimuthAbs > gapAzimuthLV1)
  {
    stepTimeXLV1 = notas [random (0, 12)];
    stepsXLV1 = duracion [random (0, 4)];
    if (motorActuar [i_azimuth] == motorXder && datoLimXder == 0)
    {
      paso (motorActuar [i_azimuth], stepTimeXLV1, stepsXLV1, 1);
    }
    if (motorActuar [i_azimuth] == motorXizq && datoLimXizq == 0)
    {
      paso (motorActuar [i_azimuth], stepTimeXLV1, stepsXLV1, 1);
    }
    flagAzimuthLV1 = 0;
  }
  else if (diferenciaAzimuthAbs < estabilizadorAzimuthLV1)
  {
    flagAzimuthLV1 = 1;
    digitalWrite (motorXder, HIGH);
    digitalWrite (motorXizq, HIGH);
  }

  if (diferenciaAltitudAbs > gapAltitudLV1)
  {
    stepTimeYLV1 = notas [random (0, 12)];
    stepsYLV1 = duracion [random (0, 4)];
    if (motorActuar [i_altitud] == motorYarr && datoLimYarriba == 0)
    {
      paso (motorActuar [i_altitud], stepTimeYLV1, stepsYLV1, 1);
    }
    if (motorActuar [i_altitud] == motorYabj && datoLimYabajo == 0)
    {
      paso (motorActuar [i_altitud], stepTimeYLV1, stepsYLV1, 1);
    }
    flagAltitudLV1 = 0;
  }
  else if (diferenciaAltitudAbs < estabilizadorAltitudLV1)
  {
    flagAltitudLV1 = 1;
    digitalWrite (motorYarr, HIGH);
    digitalWrite (motorYabj, HIGH);
  }

}

void actualizarPosicionLV2 ()
{
  bool end_lv2 = 1;
  while (end_lv2 != 0)
  {
    leerPhotocross ();
    calcularDirectivasLV2 (directivaPhotocross [0], directivaPhotocross [1]);
    //cerrarDiferenciasLV2 ();//Ya no es necesario dado que se puede integrar en los switch de directiva
    if (diferenciaAzimuthAbs > gapAzimuthLV2 && diferenciaAltitud > gapAltitudLV2)
    {
      end_lv2 = 0;
      premisaLV = 1;
    }
  }
}

void calcularDirectivasLV2 (int indicePhotocross_x, int indicePhotocross_y)
{
  //
  switch (indicePhotocross_x)
  {
    case 0:
      motorActuar [i_azimuth] = motorXizq;
      paso (motorActuar [i_azimuth], stepTimeXLV2_far, stepsXLV2_far, 1);
      flagAzimuthLV2 = 0;
      break;
    case 1:
      motorActuar [i_azimuth] = motorXizq;
      paso (motorActuar [i_azimuth], stepTimeXLV2_close, stepsXLV2_close, 1);
      flagAzimuthLV2 = 0;
      break;
    case 2:
      motorActuar [i_azimuth] = motorXizq;
      paso (motorActuar [i_azimuth], stepTimeXLV2_close, stepsXLV2_close, 1);
      flagAzimuthLV2 = 0;
      break;
    case 3:
      flagAzimuthLV2 = 1;
      digitalWrite (motorXder, HIGH);
      digitalWrite (motorXizq, HIGH);
      break;
    case 4:
      motorActuar [i_azimuth] = motorXder;
      paso (motorActuar [i_azimuth], stepTimeXLV2_close, stepsXLV2_close, 1);
      flagAzimuthLV2 = 0;
      break;
    case 5:
      motorActuar [i_azimuth] = motorXder;
      paso (motorActuar [i_azimuth], stepTimeXLV2_close, stepsXLV2_close, 1);
      flagAzimuthLV2 = 0;
      break;
    case 6:
      motorActuar [i_azimuth] = motorXder;
      paso (motorActuar [i_azimuth], stepTimeXLV2_far, stepsXLV2_far, 1);
      flagAzimuthLV2 = 0;
      break;
    default:
      digitalWrite (motorXder, HIGH);
      digitalWrite (motorXizq, HIGH);
      break;
  }

  switch (indicePhotocross_y)
  {
    case 0:
      motorActuar [i_altitud] = motorYarr;
      paso (motorActuar [i_altitud], stepTimeYLV2_far, stepsYLV2_far, 1);
      flagAltitudLV2 = 0;
      break;
    case 1:
      motorActuar [i_altitud] = motorYarr;
      paso (motorActuar [i_altitud], stepTimeYLV2_close, stepsYLV2_close, 1);
      flagAltitudLV2 = 0;
      break;
    case 2:
      motorActuar [i_altitud] = motorYarr;
      paso (motorActuar [i_altitud], stepTimeYLV2_close, stepsYLV2_close, 1);
      flagAltitudLV2 = 0;
      break;
    case 3:
      flagAltitudLV2 = 1;
      digitalWrite (motorYarr, HIGH);
      digitalWrite (motorYabj, HIGH);
      break;
    case 4:
      motorActuar [i_altitud] = motorYabj;
      paso (motorActuar [i_altitud], stepTimeYLV2_close, stepsYLV2_close, 1);
      flagAltitudLV2 = 0;
      break;
    case 5:
      motorActuar [i_altitud] = motorYabj;
      paso (motorActuar [i_altitud], stepTimeYLV2_close, stepsYLV2_close, 1);
      flagAltitudLV2 = 0;
      break;
    case 6:
      motorActuar [i_altitud] = motorYabj;
      paso (motorActuar [i_altitud], stepTimeYLV2_far, stepsYLV2_far, 1);
      flagAltitudLV2 = 0;
      break;
    default:
      digitalWrite (motorYarr, HIGH);
      digitalWrite (motorYabj, HIGH);
      break;
  }
}

