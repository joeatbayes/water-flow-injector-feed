// https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/GPIO/FunctionalInterrupt/FunctionalInterrupt.ino
// https://community.home-assistant.io/t/calibration-settings-for-yf-b10-pulse-counter/615651/2

#define S3Module_1_1
#ifdef S3Module_1_1
  #define PIN_LED 11
  #define PIN_SENSE_PWR 47
  #define PIN_TXD0 43
  #define PIN_RXD0 44
  #define PIN_TXD0_ENABLE 21
  #define PIN_MOTOR_ENABLE 16
  #define PIN_SDA 17
  #define PIN_SCL 18
  #define PIN_VSDIV 9
  #define PIN_BUP 1
  #define PIN_BDN 2
  #define PIN_BSEL 4
  #define PIN_BEX 5
  #define PIN_WSENSE1 7
  #define PIN_WSENSE2 8
  #define PIN_1WIRE 38
  #define WHITE SH110X_WHITE
  #define touchThreashold 80000
  #define SCREEN_WIDTH 128  // OLED display width, in pixels
  #define SCREEN_HEIGHT 64  // OLED display height, in pixels
  #define OLED_RESET -1     //   QT-PY / XIAO
#endif
#define serial
#define SERIAL_BAUD 115200
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <FS.h>
#include <SPIFFS.h>
/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c  //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

//Adafruit_SSD1306 display;
Adafruit_SH1106G *display;

float totLit1=0;
float totLit2=0;
float MotorStarted=0;
float MotorStopped=0;
#define MIN_MOTOR_OFF_SEC 10
#define MIN_MOTOR_ON_SEC 30

float elapSec(unsigned long startMs, unsigned long stopMs) {
  return (float)(stopMs - startMs) / 1000.0;
}

void setMotorOn() {
  if (!(digitalRead(PIN_MOTOR_ENABLE))) {
    float stopedSec = elapSec(MotorStopped, millis());
    Serial.print("motOnStopedSec="); Serial.println(stopedSec);
    if (stopedSec > MIN_MOTOR_OFF_SEC) {
      MotorStarted = millis();
      digitalWrite(PIN_MOTOR_ENABLE, HIGH);
    }
  } else {
    Serial.print("motor already on");
    // force motor to run for 30 seconds after last
    // valid attempt to turn on.
    MotorStarted = millis();
  }
}

void setMotorOff() {
  if (digitalRead(PIN_MOTOR_ENABLE)) {
    float runSec = elapSec(MotorStarted, millis());
    Serial.print("moOffRunSEc="); Serial.println(runSec);
    if (runSec > MIN_MOTOR_ON_SEC) {
      MotorStopped = millis();
      digitalWrite(PIN_MOTOR_ENABLE, LOW);
    }
  } else {
    Serial.println("motor already off");
  }
}


float pulsePerSec(unsigned long pulseCnt, float elapSec) {
  if ((pulseCnt < 1) || (elapSec < 0.00001)) {
    return 0.0;
  }
  return (float)pulseCnt / elapSec;
}

float pulsePerSec(unsigned long pulseCnt, unsigned long startMs, unsigned long stopMs) {
  return pulsePerSec(pulseCnt, elapSec(startMs, stopMs));
}

// F = (7.5* Q-4) ± 5%, Q=L/Min, error: ± 5%
float calcLPMGrediaG1Inch(float pulsesPerSec) {  
  float tmp = ((float) pulsesPerSec + 4.0) / 7.5;
  if (tmp < 0.54) {
    return 0;
  } else {
    return tmp;
  }
}
float calcLPMYFB10(float pulsesPerSec) {
  float tmp = ((float) pulsesPerSec + 8.0) / 6.0;
  if (tmp < 1.35) {
    return 0;
  } else {
    return tmp;
  }
}

float netLiterFlow(float literPerMin, float elapSec) {
  return (literPerMin / 60) * elapSec;
}


void bUpTouch() {
  Serial.println("bup");
}

void bDnTouch() {
  Serial.println("bdn");
}

void bSelTouch() {
  Serial.println("bsel");
}

void bExTouch() {
  Serial.println("bex");
}

unsigned long s1Cnt = 0;
unsigned long s1LastCalc = 0;
void pulseS1Rise() {
  s1Cnt++;
  //Serial.println("s1r");
}

unsigned long s2Cnt;
unsigned long s2LastCalc = 0;
void pulseS2Rise() {
  s2Cnt++;  
  //Serial.println("s2r");
}



void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SENSE_PWR, OUTPUT);
  pinMode(PIN_WSENSE1, INPUT);
  pinMode(PIN_WSENSE2, INPUT);
  pinMode(PIN_MOTOR_ENABLE, OUTPUT);
  digitalWrite(PIN_SENSE_PWR, HIGH);
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_MOTOR_ENABLE, LOW);
  Wire.setTimeout(3000);

  delay(40);
  Serial.begin(115200);
  Wire.begin(PIN_SDA, PIN_SCL);
  //Wire.setPins(PIN_SDA, PIN_SCL);
  delay(40);
  Serial.println("start");
  Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  display.begin(i2c_Address, true);
  Serial.println("display init");

  display.display();
  delay(40);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.println("JOE");
  display.display();
  s1LastCalc = millis();
  s2LastCalc = s1LastCalc;
  touchAttachInterrupt(PIN_BUP, bUpTouch, touchThreashold);
  touchAttachInterrupt(PIN_BDN, bDnTouch, touchThreashold);
  touchAttachInterrupt(PIN_BSEL, bSelTouch, touchThreashold);
  touchAttachInterrupt(PIN_BEX, bExTouch, touchThreashold);

  attachInterrupt(digitalPinToInterrupt(PIN_WSENSE1), pulseS1Rise, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_WSENSE2), pulseS2Rise, RISING);  
  Serial.println("end setup");
}



long cnt;
void loop() {
  cnt += 1;
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_LED, !digitalRead(PIN_LED));
  
  
  delay(1000);
  //Serial.println(cnt);
  int bur = touchRead(PIN_BUP);
  int bdr = touchRead(PIN_BDN);
  int bsr = touchRead(PIN_BSEL);
  int ber = touchRead(PIN_BEX);
  //Serial.printf("bur=%d bdr=%d bsr=%d ber=%d\n", bur, bdr, bsr, ber);

  // Take copy of our counters so the ISR can continue  
  disableInterrupt(PIN_WSENSE1);
  unsigned long currMs = millis();
  unsigned long s1CntT = s1Cnt;
  unsigned long s1LastT = s1LastCalc;
  s1Cnt = 0;
  s1LastCalc = millis();
  enableInterrupt(PIN_WSENSE1);

  disableInterrupt(PIN_WSENSE2);
  unsigned long s2CntT = s2Cnt;
  unsigned long s2LastT = s2LastCalc;
  s2Cnt = 0;  
  s2LastCalc = millis();  
  enableInterrupt(PIN_WSENSE2);


  // Now calculate or current flow rate and total liters that have flowed
  float esec1 = elapSec(s1LastT, currMs);
  float ppsec1 = pulsePerSec(s1CntT, esec1);    
  float lpm1 = calcLPMYFB10(ppsec1);
  float nlit1 = netLiterFlow(lpm1, esec1);
  totLit1 += nlit1;
  if (ppsec1 > 1) {
    Serial.print("1 cnt="); Serial.print(s1CntT);
    Serial.print(" pps="); Serial.print(ppsec1);  
    Serial.print(" esec="); Serial.print(esec1);
    Serial.print(" lpm="); Serial.print(lpm1);
    Serial.print(" nlit="); Serial.println(nlit1);  
    Serial.print(" tlit="); Serial.println(totLit1);  
  }

  float esec2 = elapSec(s2LastT, currMs);
  float ppsec2 = pulsePerSec(s2CntT, esec2);
  float lpm2 =  calcLPMGrediaG1Inch(ppsec2);
  float nlit2 = netLiterFlow(lpm2, esec2);
  totLit2 += nlit2;
  if (ppsec2 > 1) {
    Serial.print("2 cnt="); Serial.print(s2CntT);
    Serial.print(" pps="); Serial.print(ppsec2);  
    Serial.print(" esec="); Serial.print(esec2);
    Serial.print(" lpm="); Serial.print(lpm2);
    Serial.print(" nlit="); Serial.print(nlit2);  
    Serial.print(" tlit="); Serial.println(totLit2);  
  }

  if ((lpm1 > 0.1) || (lpm2 > 0.1)) {     
     setMotorOn();
  } else {
    setMotorOff();
  }
  //Serial.printf("cnt1=%ld %cnt2=%ld ppsec1=%3.3f ppsec2=%3.3f lpm1=%3.3f lpm2=%3.3f\n", 
  //   (long) s1CntT, (long) s2CntT,ppsec1, ppsec2, lpm1,lpm2);
}

