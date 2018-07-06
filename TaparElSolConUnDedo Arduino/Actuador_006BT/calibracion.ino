void calibrar ()
{
  Serial1.println ("Se entro a calibracion");
  bool calibrarBandera = 1;
  while (calibrarBandera != 0)
  {
    leerBT ();//Se espera un codigo de calibración de 2 digitos
    int buff_com = comandoBT.toInt ();
    switch (buff_com)
    {
      case 20:
        //Ayuda
        Serial1.println ("20 Ayuda");
        Serial1.println ("21 Calibrar xy");
        Serial1.println ("22 Calibrar nivel threshold de Photocross");
        Serial1.println ("29 Salir");
        comandoBT = 'null';
        break;
      case 21:
        Serial1.println ("Calibrar XY");
        calibrarXY ();
        Serial1.println ("Calibrar XY terminado");
        break;
      case 22:
        Serial1.println ("Configuracion de photocross threshold");
        thresholdPhotoCross ();
        Serial1.println ("Configurar photocross threshold terminado");
        break;
      case 29:
        calibrarBandera = 0;//Salir
        break;
      default:
        delay (1000);
        break;
    }
  }
}

void calibrarXY ()
{
  Serial1.println ("Se entro a calibrar XY");
  bool cal_x = 1;
  while (cal_x != 0)
  {
    leerBT ();
    longitudComCal = comandoBT.length ();

    switch (longitudComCal)
    {
      case 13:
        Serial1.println ("Se entro a paso calibrado");
        pasoCalibrar ();//Dar paso de calibrado
        Serial1.println ("Se dio paso calibrado");
        break;
      case 3:
        if (comandoBT == "210")
        {
          Serial1.println ("210 Ayuda");
          Serial1.println ("Instruccion de motor formato x/xxxx/xxxx/x");
          Serial1.println ("no de motor / micros de paso / no pasos / dirección");
          Serial1.println ("1-4 / 2000 - 9999 / 0004 - 9999 / 0-1");
          Serial1.println ("1 arriba, 2 abajo, 3 derecha, 4 izquierda");
          Serial1.println ("9000 lento, 6000 normal, 2000 rapido, 0200 mortal");
          Serial1.println ("4 poco, 300 ruptura de cuello");
          Serial1.println ("1 default, 0 invertir");
          Serial1.println ("211 Leer sensores de limite");
          Serial1.println ("219 salir de calibracion XY-Motor");
          comandoBT = 'null';
        }
        if (comandoBT == "211")
        {
          Serial1.println ("Se entro a la lectura de limites");
          leerLimites ();
          imprimirLimites ();
          Serial1.println ("Lectura de limites finalizada");
          comandoBT = 'null';
        }
        if (comandoBT == "219")
        {
          comandoBT = 'null';
          cal_x = 0;//Instrucción de salida
          Serial1.println ("Salir");
        }
        break;
      default:
        //default
        delay (1000);
        break;
    }
  }
}

void thresholdPhotoCross ()
{
  Serial1.println ("Se entro a Threshold Photocross");
  bool cal_pc = 1;
  while (cal_pc != 0)
  {
    leerBT ();
    longitudComCal = comandoBT.length ();
    int buff = comandoBT.toInt ();
    switch (buff)
    {
      case 220:
        Serial1.println ("220 Ayuda");
        Serial1.println ("221 leer photocross");
        Serial1.println ("222 Colocar el threshold");
        Serial1.println ("223 Consultar el threshold");
        Serial1.println ("229 salir de calibracion photocross threshold");
        comandoBT = 'null';
        break;
      case 221:
        Serial1.println ("Lectura de photocross");
        leerPhotocross ();//Monitorear
        imprimirPhotocross();
        Serial1.println ("Lectura finalizada");
        comandoBT = 'null';
        break;
      case 222:
        Serial1.println ("Configurar threshold photocross");
        setPhotocrossThreshold ();
        Serial1.println ("Se configuro el threshold de photocross");
        comandoBT = 'null';
        break;
      case 223:
        Serial1.print ("Leer el threshold del photocross");
        Serial1.println (photoThreshold);
        Serial1.print ("Lectura el threshold del photocross finalziada");
        break;
      case 229:
        cal_pc = 0;//Instrucción de salida
        comandoBT = 'null';
        Serial1.println ("salir");
        break;
      default:
        delay (1000);
        break;
    }
  }

}

void pasoCalibrar ()
{
  Serial1.println ("Se entró al paso calibrado");
  if (longitudComCal == 13)
  {
    byte calMotor;
    int calTiempo;
    int calPasos;
    bool calDir;
    String buff;
    buff = comandoBT.charAt(0);
    calMotor = buff.toInt ();
    buff = comandoBT.substring (2, 6);
    calTiempo = buff.toInt ();
    buff = comandoBT.substring (7, 11);
    calPasos = buff.toInt ();
    buff = comandoBT.charAt (12);
    calDir = buff.toInt ();
    paso (calMotor, calTiempo, calPasos, calDir);
    comandoBT = 'null';
  }
}
