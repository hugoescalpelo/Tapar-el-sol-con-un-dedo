//Bibliotecas
#include <Wire.h>//Para comunicacion I2C de brujula
#include <SPI.h>//Biblioteca usada por biblioteca de acelerómetro y brujula
#include <LSM303.h>//Biblioteca de brujula
#include <SparkFun_ADXL345.h>//biblioteca del acelerometro

//Definiciones

//Objetos
LSM303 compass;//Objeto de brujula
ADXL345 adxl = ADXL345();//Objeto del acelerometro

//Constantes

const byte pinPasos [] = {5, 4, 7, 6};//Motores
const bool dirMotores [] = {22, 24, 26, 28};
const byte ruedoLibre [] = {10,11, 8, 9};
const int avanceDemo = 40;
const int tiempoPasoDemo = 6900;
const int pasoDemo = 4;
const int tDemo = 1000;

const int photocrossPin [] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12};//PhotoCross

const byte pinLimXizq = 52;//limites
const byte pinLimXder = 50;
const byte pinLimYarriba = 48;
const byte pinLimYabajo = 46;

const bool i_azimuth = 0;//Funcionamiento
const bool i_altitud = 1;
const byte motorXder = 4;
const byte motorXizq = 3;
const byte motorYarr = 1;
const byte motorYabj = 2;

//Variables

bool inicio_bt = 0;//BT
//byte directiva = 0;
//byte longitudDirectiva = 0;
byte longitudComCal;
byte funcionarCom;

float headingF = 0.0;//Brujula

int x, y, z; //Acelerometro
float aL;

bool negX = 0, negY = 0;//Variables de signo de acelerometro

String comandoBT;//Bluetooth

int dataPhotocross [13] = {};//Photocross
byte directivaPhotocross [] = {4, 4};
int photoThreshold = 100;
int baseX, baseY;

byte datoLimXizq, datoLimXder, datoLimYarriba, datoLimYabajo;//Limites


float azimuthSol, altitudSol;//Funcionamiento
float diferenciaAzimuth, diferenciaAzimuthAbs, diferenciaAltitud, diferenciaAltitudAbs;
byte motorActuar [2] = {};
bool flagAzimuthLV1 = 0;
bool flagAltitudLV1 = 0;
bool cambioLv = 0;//cambio lv. 1 automático, 0 manual
bool lecturaSensores = 0;//0 directo, 1 promediado
bool flagAzimuthLV2 = 0;
bool flagAltitudLV2 = 0;
byte gapAzimuthLV1 = 5;//Gaps
byte gapAltitudLV1 = 5;
byte estabilizadorAzimuthLV1 = 3;
byte estabilizadorAltitudLV1 = 3;
byte gapAzimuthLV2 = 10;
byte gapAltitudLV2 = 10;
int stepTimeXLV2_far = 300;//Motores
int stepTimeXLV2_close = 200;
int stepsXLV2_far = 2;
int stepsXLV2_close = 1;

int stepTimeYLV2_far = 4300;//Motores
int stepTimeYLV2_close = 5200;
int stepsYLV2_far = 2;
int stepsYLV2_close = 1;
bool dM1, dM2, dM3, dM4;
int tiempoPasoTens = 6000;
int pasosTens = 4;
int tiempoPasoTens2 = 4000;
int pasosTens2 = 10;
bool sostSol = 0;
int stepTimeXLV1 = 9000;
int stepTimeYLV1 = 9000;
int stepsYLV1 = 80;
int stepsXLV1 = 80;
int notas [] = {9030, 9580, 8520, 8050, 7600, 7170, 6770, 6390, 6030, 5790, 7370, 5070, 4780};
int duracion [] = {160, 80, 40, 20};
int premisaLV = 1;

//Promediado
const byte MUESTRAS = 8;
int promedioHeading [MUESTRAS] = {};
int promedioAltitud [MUESTRAS] = {};
int i_promediar, i_resolver;

void setup()
{
  //Comunicacion serial
  Serial.begin (230400);//Comunicación Debug
  Serial.println ("Inicializando");
  Serial1.begin (9600);//Comunicación Bluetooth
  Serial.println ("BT Ok");
  Serial1.println ("BT Ok");

  //Inicialiación
  iniciaBrujula ();//Sensores
  iniciaAcelerometro ();
  iniciaPines ();//Pines

  //Asegurar comunicación
  esperarBT ();

  //Demo de sistemas
  if (comandoBT == "demo")
  {
    Serial.println ("Demo Iniciado");
    Serial1.println ("Demo Iniciado");
    callDemo (); //Llmamar demo
    Serial.println ("Demo finalizado. Funciona todo?");
    Serial1.println ("Demo finalizado. Funciona todo?");
  }

  comandoBT = 'null';

  //Debug
  Serial.println ("Done");
  Serial1.println ("Done");
  Serial.println ("Menu principal. Envie 0 para ayuda.");
  Serial1.println ("Menu principal. Envie 0 para ayuda.");
}

void loop()
{
  leerBT ();
  int buff_general = comandoBT.toInt ();
  switch (buff_general)
  {
    case 0:
      Serial1.println ("Ayuda");
      Serial1.println ("0 Ayuda");
      Serial1.println ("1 Demo");
      Serial1.println ("2 Calibrar");
      Serial1.println ("3 Funcionar");
      Serial1.println ("4 Leer brujula-acelerometro");
      Serial1.println ("5 Demo hasta sensores de limite");
      Serial1.println ("6 Tensar motores");
      Serial1.println ("7 Sostener/soltar");
      delay (100);
      comandoBT = 'null';
      buff_general = 9;
      break;
    case 1:
      Serial1.println ("Demo");
      callDemo ();
      comandoBT = 'null';
      buff_general = 9;
      Serial1.println ("Demo finalizado");
      break;
    case 2:
      Serial1.println ("Calibrar");
      calibrar ();
      comandoBT = 'null';
      buff_general = 9;
      Serial1.println ("Calibacion finalizada");
      break;
    case 3:
      Serial1.println ("Funcionar");
      funcionar ();
      comandoBT = 'null';
      buff_general = 9;
      Serial1.println ("Funcionamiento finalizado");
      break;
    case 4:
      Serial1.println ("Leer brujula acelerometro");
      brAccel ();
      Serial1.println ("Lectura finalizada");
      comandoBT = 'null';
      buff_general = 9;
      break;
    case 5:
      Serial1.println ("Probar motores hastael limite");
      motoresLimites ();
      comandoBT = 'null';
      buff_general = 9;
      Serial1.println ("Configuracion de limites de motor finalzada");
      break;
    case 6:
      Serial1.println ("Tensar motores");
      tensar ();
      Serial1.println ("Tension finalizada");
      comandoBT = 'null';
      buff_general = 9;
      break;
      case 7:
      Serial1.println ("Sostener/Soltar");
      sostenerSoltar ();
      Serial1.println ("Sonstener/soltar finalizado");
      comandoBT = 'null';
      buff_general = 9;
      break;
    default:
      //default
      break;
  }

  delay (1000);

}

