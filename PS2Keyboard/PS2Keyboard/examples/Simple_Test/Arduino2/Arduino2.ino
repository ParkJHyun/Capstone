#include "HX711.h"

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);
float weight;
int e = 8; // standard error
int weight_2 = 10; // barcode 2 weight
int weight_8 = 24; // barcode 8 weight
int weight_9 = 47;
int a = 0;
char barstr[2];
int SUCESS = 9;
int FAIL = 10;

void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();
  pinMode(SUCESS, OUTPUT);
  pinMode(FAIL, OUTPUT);
}

void loop() {

  weight = scale.get_units();
  weight = abs(weight);
  Serial.println(weight);
  Serial.readBytes(barstr, 1);
  Serial.print(barstr);
  if (barstr[0] == '2') //바코드가 2로 시작하는 물건을 받은 경우
  {
    delay(1000);
    if ( abs(abs(a - weight) - weight_2) < e)
    {
      a = weight;
      digitalWrite(SUCESS, LOW);
      digitalWrite(FAIL, HIGH);
    }
    else
    {
      digitalWrite(SUCESS, LOW);
      digitalWrite(FAIL, HIGH);
    }

  }
  else if (barstr[0] == '8')
  {
    delay(1000);
    if (abs(abs(a - weight) - weight_8) < e)
    {
      a = weight;
      digitalWrite(SUCESS, LOW);
      digitalWrite(FAIL, HIGH);
      delay(3000);
    }
    else
    {
      digitalWrite(SUCESS, LOW);
      digitalWrite(FAIL, HIGH);
    }
  }
  else if (barstr[0] == '9')
  {
    delay(1000);
    if (abs(abs(a - weight) - weight_9) < e)
    {
      a = weight;
      digitalWrite(SUCESS, LOW);
      digitalWrite(FAIL, HIGH);
      delay(3000);
    }
    else
    {
      digitalWrite(SUCESS, LOW);
      digitalWrite(FAIL, HIGH);
    }
  }
  else if (barstr[0] == '0')
  {
    
    delay(1000);
    a = weight;
    digitalWrite(SUCESS, LOW);
    digitalWrite(FAIL, HIGH);
  }
  else
  {
    digitalWrite(SUCESS, HIGH);
    digitalWrite(FAIL, LOW);
  }

}
