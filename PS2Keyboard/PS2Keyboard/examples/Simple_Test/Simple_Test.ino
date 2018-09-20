#include <PS2Keyboard.h>
#include <LiquidCrystal.h>
const int DataPin = 2;
const int IRQpin =  3;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
PS2Keyboard keyboard;

char c_scan[13] = {0};
char i = 0;
int total = 0; // total 금액을 저장하는 변수
int current = 0; // 현재 찍힌 금액을 보여주는 변수
char count_1, count_2, count_3 = 0; // 취소 동작(2번 스캔)에 필요한 변수
char twostr[1] = "2";
char eigstr[1] = "8";
char ninstr[1] = "9";
char delstr[1] = "0";

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

void loop() {
  delay(100);
  lcd.setCursor(12, 0);
  lcd.print(total);


  if (keyboard.available()) {

    char c = keyboard.read();

    /* PS2_ENTER는 바코드가 마지막 값을 찍었을 때 PS2_ENTER가 나타남
      숫자 값을 받았을 경우에는 선언한 배열에 한 값 씩 저장*/
    if (!(c == PS2_ENTER))
    {
      c_scan[i] = c;
      //Serial.print(c_scan[i]);
      i++;
    }
    /* PS2_ENTER를 받았을 때는 개행 작업을 수행하고 저장된 스캔 값의 첫 번째 값에 따라 동작이 나뉨
      2일 땐 TOTAL에 100을 더하고, 8일 땐 TOTAL에 50을 더한다.
    */
    if (c == PS2_ENTER) {
      Serial.println();
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
      } else if (c_scan[0] == '8')
      {
        count_2++;
        if (count_2 / 2)
        {
          total -= 200;
          lcd.setCursor(12, 1);
          lcd.print("200");
          Serial.write(delstr, 1);
          //Serial.print(total);
          //Serial.print("200");
          count_2 = 0;
        }
        else
        {
          total += 200;
          //Serial.print(total);
          lcd.setCursor(12, 1);
          lcd.print("200");
          //  Serial.print("200");
          Serial.write(eigstr, 1);
        }
      }
      else if (c_scan[0] == '9')
      {
        count_3++;
        if (count_3 / 2)
        {
          total -= 300;
          lcd.setCursor(12, 1);
          lcd.print("300");
          Serial.write(delstr, 1);
          count_3 = 0;
        }
        else
        {
          total += 300;
          lcd.setCursor(12, 1);
          lcd.print("300");
          Serial.write(ninstr, 1);
        }
      }


      /* 모든 작업이 끝이 나면 저장했던 바코드 값을 Initialize 하여 새로운 바코드 값을 받을 준비한다.*/
      for (i = 0; i < 13; i++) c_scan[i] = 0;
      i = 0;
    }
  }
}
