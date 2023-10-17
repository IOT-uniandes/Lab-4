int IRSensor = 2;
int led = 13;

void setup(){
  Serial.begin(115200);
  pinMode (IRSensor, INPUT);
}


void loop(){
  int estado = digitalRead(IRSensor);
  if(estado == 1){
    digitalWrite(led, LOW);
    delay(500);
  }else{
    digitalWrite(led, HIGH);
    delay(500); 
  }
}
