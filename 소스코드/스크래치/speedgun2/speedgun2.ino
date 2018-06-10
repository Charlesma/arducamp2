#include <Wire.h>                        // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 1602 I2C용 라이브러리

int MOTION_IN_1 = 2;
int MOTION_IN_2 = 4;

LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);             // 1번째, 1라인
  lcd.print("Speedgun");
  
  Serial.begin(9600);
  pinMode(MOTION_IN_1, INPUT);
  pinMode(MOTION_IN_2, INPUT);
}


unsigned long pre_time = 0;
unsigned long cur_time = 0;
bool mode1 = false;
bool mode2 = false;
void loop() {

  if (digitalRead(MOTION_IN_1) == HIGH) {
    if (mode1 == false) {
      Serial.println("Number 1 HIGH");
      pre_time = (unsigned long)millis();
      mode1 = true;
    }
  }
  else {
    if (mode1 && (millis() - pre_time) > 1000) {
      mode1 = false;
      Serial.println("Number 1 : Low");
    }
  }

  if (digitalRead(MOTION_IN_2) == HIGH) {
    if (mode1 == true && mode2 == false) {
      Serial.println("Number 2 : HIGH");
      cur_time = (unsigned long)millis();
      float km_per_hour = 3600 * 0.0004 / (cur_time - pre_time) * 1000;
      Serial.println(cur_time - pre_time);
      Serial.println(String(km_per_hour) + " km/h");

      lcd.setCursor(0,1);             // 1번째, 2라인
      lcd.print(String(km_per_hour) + " km/h");

      mode2 = true;
    }
  }
  else {
    if (mode2 && (millis() - cur_time) > 1000) {
      mode2 = false;
      Serial.println("Number 2 : Low");
    }
  }
}

