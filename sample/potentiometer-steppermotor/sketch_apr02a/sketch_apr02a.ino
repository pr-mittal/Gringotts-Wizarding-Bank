
int v=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  v=analogRead(A0);
  Serial.println(v);
  analogWrite(A1,v);
  analogWrite(A5,v);
  delay(v);
  delay(1000);
  digitalWrite(13,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  
  delay(v);
  delay(1000);
  digitalWrite(13,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  
}
