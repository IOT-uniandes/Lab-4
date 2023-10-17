int IRSensor1 = 2;
int IRSensor2 = 3;
int IRSensor3 = 4;
int IRSensor4 = 5;
int IRSensor5 = 6;
int IRSensor6 = 7;
int IRSensor7 = 8;
int IRSensor8 = 9;

int led = 13;

int prevState1;
int prevState2;
int prevState3;
int prevState4;
int prevState5;
int prevState6;
int prevState7;
int prevState8;

unsigned long currentTime;
unsigned long lastPrintTime;

/****************************************
 * Main Functions
 ****************************************/
 
void setup() {
  Serial.begin(115200);

  pinMode(IRSensor1, INPUT);
  pinMode(IRSensor2, INPUT);
  pinMode(IRSensor3, INPUT);
  pinMode(IRSensor4, INPUT);
  pinMode(IRSensor5, INPUT);
  pinMode(IRSensor6, INPUT);
  pinMode(IRSensor7, INPUT);
  pinMode(IRSensor8, INPUT);

  int prevState1 = digitalRead(IRSensor1);
  int prevState2 = digitalRead(IRSensor2);
  int prevState3 = digitalRead(IRSensor3);
  int prevState4 = digitalRead(IRSensor4);
  int prevState5 = digitalRead(IRSensor5);
  int prevState6 = digitalRead(IRSensor6);
  int prevState7 = digitalRead(IRSensor7);
  int prevState8 = digitalRead(IRSensor8);

  pinMode(led, OUTPUT);
}

void loop() {    
    int state1 = digitalRead(IRSensor1);
    int state2 = digitalRead(IRSensor2);
    int state3 = digitalRead(IRSensor3);
    int state4 = digitalRead(IRSensor4);
    int state5 = digitalRead(IRSensor5);
    int state6 = digitalRead(IRSensor6);
    int state7 = digitalRead(IRSensor7);
    int state8 = digitalRead(IRSensor8);

    currentTime = millis();

    if (currentTime - lastPrintTime >= 2000) {

      if (
        state1 != prevState1 ||
        state2 != prevState2 ||
        state3 != prevState3 ||
        state4 != prevState4 ||
        state5 != prevState5 ||
        state6 != prevState6 ||
        state7 != prevState7 ||
        state8 != prevState8
        ) {

        String data = String(state1) + "," + String(state2) + "," + String(state3) + "," + String(state4) + "," + String(state5) + "," + String(state6) + "," + String(state7) + "," + String(state8);
        
        prevState1 = state1;
        prevState2 = state2;
        prevState3 = state3;
        prevState4 = state4;
        prevState5 = state5;
        prevState6 = state6;
        prevState7 = state7;
        prevState8 = state8;

        Serial.println(data);

        lastPrintTime = currentTime;
      }

    }

    delay(100);
}

