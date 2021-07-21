void setup() {
  // put your setup code here, to run once:
  //rgb-210
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  
}
const int Black=0;
const int red=1;
const int green=2;
const int yellow=3;
const int blue=4;
const int magenta=5;
const int cyan=6;
const int white=7;
void loop() {
  // put your main code here, to run repeatedly:
  for(int i=Black;i<=white;i++){
    if(i==Black){
      digitalWrite(0,0);digitalWrite(1,0);digitalWrite(2,0);
    }
    if(i==red){
      digitalWrite(0,0);digitalWrite(1,0);digitalWrite(2,1);
    }
    if(i==green){
      digitalWrite(0,0);digitalWrite(1,1);digitalWrite(2,0);
    }
    if(i==yellow){
      digitalWrite(0,0);digitalWrite(1,1);digitalWrite(2,1);
    }
    if(i==blue){
      digitalWrite(0,1);digitalWrite(1,0);digitalWrite(2,0);
    }
    if(i==magenta){
      digitalWrite(0,1);digitalWrite(1,0);digitalWrite(2,1);
    }
    if(i==cyan){
      digitalWrite(0,1);digitalWrite(1,1);digitalWrite(2,0);
    }
    if(i==white){
      digitalWrite(0,1);digitalWrite(1,1);digitalWrite(2,1);
    }
    delay(1000);
  }
}
