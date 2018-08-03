/*
   Ivan Abreu Studio.

   23/07/2018

   This code controls 4 stepper motors, and an absolute orientation sensor.

   This is for an Ivan Abreu's Art Work. This piece purpose is to make the
   host is to cover the sun with a finger

   Changelog:
   V0.1 BT handshake
   V0.1.1 Motor decalration
   V0.1.2 Test sequence
   V0.1.3 Menu added
   V0.1.4 Test sequence added
   V0.1.5 Run all & drive all sequence Added
   V0.1.6 BNO055 sensor Added
   V0.1.7 Test & motor orientation fixed
   V0.1.8 Running termination condition fixed
   V0.1.9 Toggle Enable Motors added
   V0.2 Azimuth motors tested
   V0.3 Altitude motors tested. MPA reached (Minimum Product Available


   Team
   Iván Abreu Ochoa
   Malitzin Cortes
   Beto Olguin
   Hugo Vargas

*/

//Libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//Constants
const int HANDSHAKE_CODE = 1500;

const byte PIN [] = {4, 5, 6, 7};
const byte ENABLE [] = {8, 9, 10, 11};
const byte DIR [] = {22, 24, 26, 28};
const byte LEFT_MOTOR = 2;
const byte RIGHT_MOTOR = 3;
const byte FRONT_MOTOR = 0;
const byte REAR_MOTOR = 1;
const byte N_MOTORS = 4;

const bool LEFT_DIR = 0;
const bool RIGHT_DIR = 1;
const bool PULL_DIR = 1;
const bool LOOSE_DIR = 0;
const long TIME_TESTEPS = 3200;//Microseconds
const bool ON = 1;
const bool OFF = 0;
const long TEST_STEPS = 500;
const int IBWTT = 500; //In Betweent Wait Test Time in Millis

const long RUN_SAMPLE = 50000;

#define BNO055_SAMPLERATE_DELAY_MS (100)

//Objects
Adafruit_BNO055 bno = Adafruit_BNO055();
String rValueBT;

//Variables
int buffBT;
//String rValueBT;

bool dirMotor [] = {0, 0, 0, 0};
long stepMotorTime [] = {0, 0, 0, 0};
bool runMotor [] = {0, 0, 0, 0};
long stepTimeTarget [] = {0, 0, 0, 0};
bool enableMotor [] = {0, 0, 0, 0};

long stepRegistry [] = {0, 0, 0, 0};

long timeNow;
bool levelMotor [] = {0, 0, 0, 0};

long AOSensorTime;
int buffMag;
int heading;
int tilting;
bool stopSearch = 0;
float azimuthSol = 0;
float altitudSol = 0;
float lastAz, lastAl;
long reportData;

int diffference;
bool workingDirLeft, workingDirRight;
int azimuthLeft;
int threshold = 3;
bool closeEnoughAz;
long runSample;
long workingAzimuthTimeStep;
int diferenccce;
bool workingDirFront, workingDirRear;
int altitudLeft;
bool closeEnoughAl;
long workingAltitudTimeStep;

bool enableToggle = 0;

void setup () {
  Serial.begin (2000000);
  Serial.println ("Setting Up");

  Serial1.begin (9600);
  Serial1.println ("BT started");

  setPinModes ();
  setInitials ();

  waitHandShake ();

  printMenu ();
  clean ();
}

void loop () {
  readBT ();
  buffBT = rValueBT.toInt ();
  switch (buffBT) {
    case 0:
      printMenu ();
      clean ();
      break;
    case 1:
      Serial.println ("Test sequence in progreess");
      Serial1.println ("Test sequence in progress");
      testSequence ();
      Serial.println ("Test sequence done");
      Serial1.println ("Test Sequence Done");
      clean ();
      break;
    case 2:
      Serial.println ("Begin Orientation Sensor");
      Serial1.println ("Begin Orientation Sensor");
      beginOrientationSensor ();
      Serial.println ("Absolute Orientation Sensor started");
      Serial1.println ("Absolute Orientation Sensor started");
      clean ();
      break;
    case 3:
      Serial.println ("Calibrating Absolute Orientation Sensor");
      Serial1.println ("Calibrating Absolute Orientation Sensor");
      runUntilCalibrate ();
      Serial.println (buffMag);
      clean ();
      Serial.println ("Compass Absolute Orientation Sensor calibrated");
      Serial1.println ("Compass Absolute Orientation Sensor calibrated");
      break;
    case 4:
      Serial.println ("Running");
      Serial1.println ("Running");
      searchSun ();
      Serial.println (";)");
      Serial1.println (";)");
      clean ();
      break;
    case 5:
      //motorMenu ();
      clean ();
      break;
    case 6:
      enableToggleMenu ();
      Serial.print ("All motors ");
      Serial.println (enableToggle);
      Serial1.print ("All Motors ");
      Serial1.println (enableToggle);
      clean ();
      break;
    default:
      //Serial.println ("Try again");
      //Serial1.println ("Try Again");
      //printMenu ();
      clean ();
      break;
  }
}

