void automaticos ()
{
  Serial1.println ("Se entro a la configuracion de automaticos");
  bool auto_f = 1;
  while (auto_f != 0)
  {
    leerBT ();
    int buff_auto = comandoBT.toInt ();
    switch (buff_auto)
    {
      case 340:
        Serial1.println ("340 Ayuda");
        Serial1.println ("341 Switch LV1-LV2 Automatico-Manual");
        Serial1.println ("342 Cambiar lecturas promediadas-crudas");
        Serial1.println ("349 Salir");
        comandoBT = 'null';
        break;
      case 341:
        Serial1.println ("Cambio LV1-LV2 Automatico-Manual");
        configuraCambioLV ();
        Serial1.println ("Cambio LV1-LV2 Automatico-Manual finalizado ");
        comandoBT = 'null';
        break;
      case 342:
        Serial1.println ("Cambio entre lecturas promediadas-crudas");
        configuraLecturas ();
        Serial1.println ("Cambio entre lecturas promediadas-crudas finalizado ");
        comandoBT = 'null';
        break;
      case 349:
        auto_f = 0;
        comandoBT = 'null';
        Serial1.println ("Salir");
        break;
      default:
        delay (1000);
        break;
    }
  }
}

void configuraCambioLV ()
{
  if (cambioLv == 1)
  {
    Serial1.println ("Se configuro cambio LV a manual");
    cambioLv = 0;
  }
  if (cambioLv == 0)
  {
    Serial1.println ("Se configuro cambio LV a automatico");
    cambioLv = 1;
  }
}

void configuraLecturas ()
{
  if (lecturaSensores == 1)
  {
    Serial1.println ("Se configuro cambio lectura de sensores a directa");
    lecturaSensores = 0;
  }
  if (lecturaSensores == 0)
  {
    Serial1.println ("Se configuro cambio lectura de sensores a promediada");
    lecturaSensores = 1;
  }
}
