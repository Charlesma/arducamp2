int MOTION_IN_1 = 2;
int MOTION_IN_2 = 4;
int LED_OUT = 13;

void setup() {
  Serial.begin(9600);
  pinMode(MOTION_IN_1, INPUT);
  pinMode(MOTION_IN_2, INPUT);
  pinMode(LED_OUT, OUTPUT);
}


unsigned long pre_time = 0;
unsigned long cur_time = 0;
bool mode1 = false;
bool mode2 = false;
void loop() {

  if (digitalRead(MOTION_IN_1) == HIGH) {
    if (mode1 == false) {
      Serial.println("Number 1");
      pre_time = (unsigned long)millis();
      mode1 = true;
    }
  }
  else {
    if (mode1) {
      mode1 = false;
      Serial.println("free 1");
    }
  }

  if (digitalRead(MOTION_IN_2) == HIGH) {
    if (mode1 == true && mode2 == false) {
      Serial.println("Number 2");
      cur_time = (unsigned long)millis();
      float km_per_hour = 3600 * 0.0004 / (cur_time - pre_time) * 1000;
      Serial.println(cur_time - pre_time);
      Serial.println(String(km_per_hour) + " km/hour");

      mode2 = true;
    }
  }
  else {
    if (mode2) {
      mode2 = false;
      Serial.println("free 2");
    }
  }

  if (mode1 == false && mode2 == false) {
    digitalWrite(LED_OUT, HIGH);
  } else {
    digitalWrite(LED_OUT, LOW);
  }
}

