//Para hacer map con variables tipo float y obtener resultados float
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//La funcion paso selecciona el motor y sus pines. Hereda todo lo necesario a ActuadorPasos
void paso (byte motor, int stepTime, int steps, bool direcMotor)
{
  byte stepPin;
  byte enableMotor;
  byte pinDir;

  switch (motor)
  {
    case 1:
      enableMotor = ruedoLibre [0];
      stepPin = pinPasos [0];
      pinDir = dirMotores [0];
      actuadorPasos (enableMotor, steps, stepPin, stepTime, direcMotor, pinDir);
      break;
    case 2:
      enableMotor = ruedoLibre [1];
      stepPin = pinPasos [1];
      pinDir = dirMotores [1];
      actuadorPasos (enableMotor, steps, stepPin, stepTime, direcMotor, pinDir);
      break;
    case 3:
      enableMotor = ruedoLibre [2];
      stepPin = pinPasos [2];
      pinDir = dirMotores [2];
      actuadorPasos (enableMotor, steps, stepPin, stepTime, direcMotor, pinDir);
      break;
    case 4:
      enableMotor = ruedoLibre [3];
      stepPin = pinPasos [3];
      pinDir = dirMotores [3];
      actuadorPasos (enableMotor, steps, stepPin, stepTime, direcMotor, pinDir);
      break;
    default:
      //
      break;
  }
}

void actuadorPasos (byte enMot, int st, byte stPn, int stTm, bool dirMot, byte pnDr)
{
  byte contraEnMot;
  if (enMot == ruedoLibre [0])
  {
    contraEnMot = ruedoLibre [1];
  }
  if (enMot == ruedoLibre [1])
  {
    contraEnMot = ruedoLibre [0];
  }
  if (enMot == ruedoLibre [2])
  {
    contraEnMot = ruedoLibre [3];
  }
  if (enMot == ruedoLibre [3])
  {
    contraEnMot = ruedoLibre [2];
  }
  digitalWrite (pnDr, dirMot);
  digitalWrite (enMot, HIGH);
  digitalWrite (contraEnMot, LOW);
  for (int i_step = 0; i_step < st; i_step++)
  {
    digitalWrite (stPn, HIGH);
    delayMicroseconds (stTm);
    digitalWrite (stPn, LOW);
    delayMicroseconds (stTm);
  }
  digitalWrite (enMot, HIGH);
  digitalWrite (contraEnMot, HIGH);
}

void motoresLimites ()
{
  datoLimXizq = digitalRead (pinLimXizq);
  while (datoLimXizq != 1)
  {
    actuadorPasos (ruedoLibre [0], pasoDemo, pinPasos [0], tiempoPasoDemo, 1, dirMotores [0]);
    datoLimXizq = digitalRead (pinLimXizq);
  }
  int largo = 0;
  datoLimXizq = digitalRead (pinLimXizq);
  while (datoLimXder != 1)
  {
    actuadorPasos (ruedoLibre [1], pasoDemo, pinPasos [1], tiempoPasoDemo, 1, dirMotores [1]);
    datoLimXizq = digitalRead (pinLimXizq);
    largo++;
  }
  largo = largo / 2;
  for (int reg = 0; reg < largo; reg++)
  {
    actuadorPasos (ruedoLibre [0], pasoDemo, pinPasos [0], tiempoPasoDemo, 1, dirMotores [0]);
  }

  datoLimYarriba = digitalRead (pinLimYarriba);
  while (datoLimYarriba != 1)
  {
    actuadorPasos (ruedoLibre [2], pasoDemo, pinPasos [2], tiempoPasoDemo, 1, dirMotores [2]);
    datoLimYarriba = digitalRead (pinLimYarriba);
  }
  int alto = 0;
  datoLimYabajo = digitalRead (pinLimYabajo);
  while (datoLimYabajo != 1)
  {
    actuadorPasos (ruedoLibre [3], pasoDemo, pinPasos [3], tiempoPasoDemo, 1, dirMotores [3]);
    datoLimYabajo = digitalRead (pinLimYabajo);
    alto++;
  }
  alto = alto / 2;
  for (int reg = 0; reg < alto; reg++)
  {
    actuadorPasos (ruedoLibre [2], pasoDemo, pinPasos [2], tiempoPasoDemo, 1, dirMotores [2]);
  }
}

void tensar ()
{
  Serial1.println ("Se entro a tensado");
  for (int i_t = 0; i_t < pasosTens; i_t++)
  {
  paso (motorXder, tiempoPasoTens, 20, 1);
  paso (motorXizq, tiempoPasoTens, 20, 1);
  paso (motorYarr, tiempoPasoTens, 20, 1);
  paso (motorYabj, tiempoPasoTens, 20, 1);  
  }
}

void tensar2 ()
{
  Serial1.println ("Se entro a tensado lv1");
  if (motorActuar [i_azimuth] == motorXder)
  {
    paso (motorXizq, tiempoPasoTens2, pasosTens2, 1);
  }
  if (motorActuar [i_azimuth] == motorXizq)
  {
    paso (motorXder, tiempoPasoTens2, pasosTens2, 1);
  }
  if (motorActuar [i_altitud] == motorYarr)
  {
    paso (motorYabj, tiempoPasoTens2, pasosTens2, 1);
  }
  if (motorActuar [i_altitud] == motorYabj)
  {
    paso (motorYarr, tiempoPasoTens2, pasosTens2, 1);
  }
}

void sostenerSoltar ()
{
  if (sostSol == 0)
  {
    sostSol = 1;
    digitalWrite (ruedoLibre [0], HIGH);
    digitalWrite (ruedoLibre [1], HIGH);
    digitalWrite (ruedoLibre [2], HIGH);
    digitalWrite (ruedoLibre [3], HIGH);
    Serial1.println ("Todo esta sostenido");
  } 
  else
  {
    sostSol = 0;
    digitalWrite (ruedoLibre [0], LOW);
    digitalWrite (ruedoLibre [1], LOW);
    digitalWrite (ruedoLibre [2], LOW);
    digitalWrite (ruedoLibre [3], LOW);
    Serial1.println ("Todo esta suelto");
  }
}

