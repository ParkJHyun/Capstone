# Capstone

<img width="600" src="https://user-images.githubusercontent.com/35755034/45800111-cea3a380-bcea-11e8-9fd9-defd6caf6153.png">

창의적 종합설계 **"삑 그리고 다음"** 스마트 카트 아두이노 코드입니다.

[![Alt text for your video](https://user-images.githubusercontent.com/35755034/45801264-5b039580-bcee-11e8-9735-91e7219b9852.jpg)](https://www.youtube.com/embed/wW5VpyIPEhY)

(위 이미지를 클릭하시면 영상을 확인할 수 있습니다.)

## 1. Master Arduino code (LCD)

examples -> Simple_Test -> Simple_Test.ino 실행

``` ino
void setup() {
  delay(100);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.println("Total : ");
  Serial.print("Current : ");
  lcd.print("Total : ");
  lcd.setCursor(0, 1);
  lcd.print("Current : ");
}
```
setup 함수에서는 바코드 스캐너와 통신을 하기위하여 초기화 과정과 아두이노끼리의 Serial 통신을 위한 초기화 과정과 
LCD에 가격을 출력하기 위한 초기화 과정을 거쳐 LCD에 기본적인 내용 출력을 설정합니다.

loop 문에는 바코드 스캐너로 부터 얻어온 값들을 비교하여 각각의 조건에 따라 동작을 나누었습니다.
``` ino
   if (c_scan[0] == '2')
      {
        count_1++;
        if (count_1 / 2)
        {
          total -= 100;
          lcd.setCursor(12, 1);
          lcd.print("100");
          Serial.write(delstr, 1);
          //   Serial.print(total);
          // Serial.print("100");
          count_1 = 0;
        }
        else
        {
          total += 100;
          lcd.setCursor(12, 1);
          lcd.print("100");
          //  Serial.print(total);
          //  Serial.print("100");
          Serial.write(twostr, 1);
        }
      } 
```
count 변수는 한 번 찍으면 계산되어 카트에 넣을 수 있고, 두 번 찍으면 카트에 담겨져 있는 상품을 취소할 수 있게 
찍는 횟수를 저장합니다.
count 변수에 저장된 값이 홀수/짝수에 따라 total 값에 해당 상품이 추가될지, 취소될지 결정됩니다.
``` ino
      for (i = 0; i < 13; i++) c_scan[i] = 0;
      i = 0;
```
모든 과정이 끝이 나면 바코드 스캐너를 통해 저장했던 변수를 다시 0으로 초기화 시킵니다.

## 2. Slave Arduino code (Load Cell)

examples -> Simple_Test -> Arduino2 -> Arduino2.ino 실행

``` ino
void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();
  pinMode(SUCESS, OUTPUT);
  pinMode(FAIL, OUTPUT);
}
```
Arduino 2에서는 로드 셀을 이용하여 해당 제품의 무게를 측정합니다. 

Arduino 1과의 Serial 통신을 위한 작업과 로드 셀 센서 값에 대해서 보정 과정을 거칩니다.

뿐만 아니라 오류 상황인지 성공적인 상황인지 확인하기 위한 LED 핀 모드도 설정합니다.

loop 문에서는 스캐너를 통해 받은 데이터가 들어왔을 경우에 이전의 카트 안에 담겨있는 무게 값과 새로 추가된 전체 무게 값이
오차 안에 속해있다면 즉, 스캐너가 찍은 물건과 담은 물건이 동일하다면 LED를 통해 성공적임을 알립니다.

만약 그렇지 않다면 빨간색 LED에 불이 켜집니다.

``` ino
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
```
취소 모드일 경우에는 Arduino 2에 0번 값을 받게 되고 취소되고 난 후의 무게 값을 현재 무게 값으로 저장합니다.

``` ino
  else if (barstr[0] == '0')
  {
    
    delay(1000);
    a = weight;
    digitalWrite(SUCESS, LOW);
    digitalWrite(FAIL, HIGH);
  }
```

**작동영상은 추가예정입니다.
