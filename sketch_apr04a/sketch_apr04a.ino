// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DT A0
#define SCK A1
#define sw 2

long sample=0;
float val=0;
long count=0;

void setup() {
  Serial.begin(9600);
  pinMode(SCK, OUTPUT);
  pinMode(sw, INPUT_PULLUP);//set sw to default 1
  lcd.begin(16, 2);
  lcd.print("    Weight ");
  lcd.setCursor(0,1);
  lcd.print(" Measurement ");
  delay(1000);
  lcd.clear();
  calibrate();//calibrating the weight scale
}

void loop() {
  count= readCount();
  int w=((count-sample)/val);
  Serial.print("weight:");
  Serial.print((int)w);
  Serial.println("g");
  lcd.setCursor(0,0);
  lcd.print("Weight            ");
  lcd.setCursor(0,1);
  lcd.print(w);
  lcd.print("g             ");

  if(digitalRead(sw)==0)
  {
    val=0;
    sample=0;
    w=0;
    count=0;
    calibrate();
  }
}

void calibrate()
{
  lcd.clear();
  lcd.print("Calibrating...");
  lcd.setCursor(0,1);
  lcd.print("Please Wait...");
  for(int i=0;i<100;i++)
  {
    count=readCount();
    sample+=count;
    Serial.println(count);
  }
  sample/=100;
  lcd.print("Avg:");
  lcd.setCursor(0,1);
  lcd.println(sample);//basically weight due to atmosphere
  delay(1000);
  lcd.clear();
  
  lcd.print("Put 100g & wait");
  //lcd.setCursor(0,1);
  count=0;
  while(count<1000)
  {
    count=readCount();
    count=sample-count;
    //lcd.println(count);
  }
  
  lcd.clear();
  lcd.print("Please Wait....");
  //lcd.setCursor(0,1);
  delay(2000);
  for(int i=0;i<100;i++)
  {
    count=readCount();
    val+=count-sample;
    //lcd.println(sample-count);
  }
  val=val/100.0;//taking average
  //the value we have now is the weight of 100gm sample, so value of 1gm sample is val/100
  val=val/100.0;// put here your calibrating weight
  if(val==0){
    //no 100gm sample was put,the output of scale will be simply the readCount,see void loop()
    val=1;
  }
  lcd.print("Avg:");
  lcd.setCursor(0,1);
  lcd.println(val);//basically weight due to atmosphere
  delay(1000);
  lcd.clear();
}
//reading data and writing input to HX711
unsigned long readCount(void)
{
  unsigned long Count;
  unsigned char i;
  pinMode(DT, OUTPUT);
  digitalWrite(DT,HIGH);
  digitalWrite(SCK,LOW);
  Count=0;
  pinMode(DT, INPUT);
  while(digitalRead(DT));
  for (i=0;i<24;i++)
  {
    digitalWrite(SCK,HIGH);
    Count=Count<<1;
    digitalWrite(SCK,LOW);
    if(digitalRead(DT)) 
    Count++;
  }
  digitalWrite(SCK,HIGH);
  Count=Count^0x800000;
  digitalWrite(SCK,LOW);
  return(Count);
}
