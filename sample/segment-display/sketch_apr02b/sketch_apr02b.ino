void setup() {
  // put your setup code here, to run once:
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //0
  digitalWrite(0,HIGH);digitalWrite(1,HIGH);digitalWrite(2,HIGH);digitalWrite(3,HIGH);digitalWrite(4,HIGH);digitalWrite(5,HIGH);digitalWrite(6,LOW);
  delay(1000);
  //1
  digitalWrite(0,LOW);digitalWrite(1,HIGH);digitalWrite(2,HIGH);digitalWrite(3,LOW);digitalWrite(4,LOW);digitalWrite(5,LOW);digitalWrite(6,LOW);
  delay(1000);
  //2
  digitalWrite(0,HIGH);digitalWrite(1,HIGH);digitalWrite(2,LOW);digitalWrite(3,HIGH);digitalWrite(4,HIGH);digitalWrite(5,LOW);digitalWrite(6,HIGH);
  delay(1000);
  //3
  digitalWrite(0,HIGH);digitalWrite(1,HIGH);digitalWrite(2,HIGH);digitalWrite(3,HIGH);digitalWrite(4,LOW);digitalWrite(5,LOW);digitalWrite(6,HIGH);
  delay(1000);
  //4
  digitalWrite(0,LOW);digitalWrite(1,HIGH);digitalWrite(2,HIGH);digitalWrite(3,LOW);digitalWrite(4,LOW);digitalWrite(5,HIGH);digitalWrite(6,HIGH);
  delay(1000);
  //5
  digitalWrite(0,HIGH);digitalWrite(1,LOW);digitalWrite(2,HIGH);digitalWrite(3,HIGH);digitalWrite(4,LOW);digitalWrite(5,HIGH);digitalWrite(6,HIGH);
  delay(1000);
  //6
  digitalWrite(0,HIGH);digitalWrite(1,LOW);digitalWrite(2,HIGH);digitalWrite(3,HIGH);digitalWrite(4,HIGH);digitalWrite(5,HIGH);digitalWrite(6,HIGH);
  delay(1000);
  //7
  digitalWrite(0,HIGH);digitalWrite(1,HIGH);digitalWrite(2,HIGH);digitalWrite(3,LOW);digitalWrite(4,LOW);digitalWrite(5,LOW);digitalWrite(6,LOW);
  delay(1000);
  //8
  digitalWrite(0,HIGH);digitalWrite(1,HIGH);digitalWrite(2,HIGH);digitalWrite(3,HIGH);digitalWrite(4,HIGH);digitalWrite(5,HIGH);digitalWrite(6,HIGH);
  delay(1000);
  digitalWrite(0,HIGH);digitalWrite(1,HIGH);digitalWrite(2,HIGH);digitalWrite(3,LOW);digitalWrite(4,LOW);digitalWrite(5,HIGH);digitalWrite(6,HIGH);
  delay(1000);
}
