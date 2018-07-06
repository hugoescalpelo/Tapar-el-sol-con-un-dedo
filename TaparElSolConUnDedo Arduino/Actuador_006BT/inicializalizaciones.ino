void iniciaBrujula ()
{
  Wire.begin ();//Iniciar comunicación I2C
  compass.init ();//Inicialiazar brujula
  compass.enableDefault ();//Condiciones default

  //Calibrar
  compass.m_min = (LSM303::vector<int16_t>) {
    -32767, -32767, -32767
  };
  compass.m_max = (LSM303::vector<int16_t>) {
    +32767, +32767, +32767
  };
}

void iniciaAcelerometro ()
{
  adxl.powerOn();                     // Power on the ADXL345
  adxl.setRangeSetting(2);           // Give the range settings
  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
  adxl.setActivityXYZ(1, 0, 0);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)
  adxl.setInactivityXYZ(1, 0, 0);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setInactivityThreshold(75);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
  adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?
  adxl.setTapDetectionOnXYZ(0, 0, 1); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)

  // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
  adxl.setTapThreshold(50);           // 62.5 mg per increment
  adxl.setTapDuration(15);            // 625 μs per increment
  adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
  adxl.setDoubleTapWindow(200);       // 1.25 ms per increment

  // Set values for what is considered FREE FALL (0-255)
  adxl.setFreeFallThreshold(7);       // (5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment

  // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
  adxl.InactivityINT(1);
  adxl.ActivityINT(1);
  adxl.FreeFallINT(1);
  adxl.doubleTapINT(1);
  adxl.singleTapINT(1);
}

void iniciaPines ()
{
  for (int i_pn = 0; i_pn < 4; i_pn++)
  {
    pinMode (pinPasos [i_pn], OUTPUT);
    pinMode (ruedoLibre [i_pn], OUTPUT);
    pinMode (dirMotores [i_pn], OUTPUT);
  }
  pinMode (pinLimXizq, INPUT);
  pinMode (pinLimXder, INPUT);
  pinMode (pinLimYarriba, INPUT);
  pinMode (pinLimYabajo, INPUT);
  sostenerSoltar ();
}

