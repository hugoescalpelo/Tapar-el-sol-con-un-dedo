/*
   Ivan Abreu Studio.

   12/07/2018

   This code controls 4 stepper motors, and an absolute orientation sensor.

   This is for an Ivan Abreu's Art Work. This piece purpose is to make the
   host is to cover the sun with a finger

   Changelog:
   V0.1 BT handshake
   V0.1.1 Motor decalration
   V0.1.2 Test sequence
   V0.1.3 Menu added


   Team
   Iván Abreu Ochoa
   Malitzin Cortes
   Beto Olguin
   Hugo Vargas

*/

//Libraries

//Objects

//Constants
const int HANDSHAKE_CODE = 1500;

const byte PIN [] = {4, 5, 6, 7};
const byte ENABLE [] = {8, 9, 10, 11};
const byte DIR [] = {22, 24, 26, 28};
const byte LEFT_MOTOR = 0;
const byte RIGHT_MOTOR = 1;
const byte FRONT_MOTOR = 2;
const byte REAR_MOTOR = 3;
const byte N_MOTORS = 4;

const bool LEFT_DIR = 0;
const bool RIGHT_DIR = 1;
const bool PULL_DIR = 1;
const bool LOOSE_DIR = 0;
const long TIME_TESTEPS = 1200;//Microseconds
const bool ON = 1;
const bool OFF = 0;
const long TEST_STEPS = 1500;
const int IBWTT = 500; //In Betweent Wait Test Time in Millis

//Variables
int buffBT;
String rValueBT;

bool dirMotor [] = {0, 0, 0, 0};
long stepMotorTime [] = {0, 0, 0, 0};
bool runMotor [] = {0, 0, 0, 0};
long stepTimeTarget [] = {0, 0, 0, 0};
bool enableMotor [] = {0, 0, 0, 0};

long positionSteps [] = {0, 0, 0, 0};

long timeNow;
bool levelMotor [] = {0, 0, 0, 0};

void setup () {
  Serial.begin (2000000);
  Serial.println ("Setting Up");

  setPinModes ();
  setInitials ();

  waitHandShake ();
  waitTest ();

  printMenu ();
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
    testSequence ();
    clean ();
    break;
    case 2:
    //CalibrateMenu ();
    clean ();
    break;
    case 3:
    //coverSun ();
    clean ();
    break;
    case 4:
    //sensorMenu ();
    clean ();
    break;
    case 5:
    //motorMenu ();
    clean ();
    break;
    case 6:
    //enableToggleMenu ();
    clean ();
    break;
    default:
    Serial.println ("Try again");
    Serial1.println ("Try Again");
    printMenu ();
    clean ();
    break;
  }
}

