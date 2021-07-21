// include the library code:
#include <LiquidCrystal.h>
//#include "SoftwareSerial.h"
#include <TinyGPS.h>
#include <BlynkSimpleStream.h>

////////////////////////////////lcd//////////////////////////////
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 24, en = 25, d4 = 26, d5 = 27, d6 = 28, d7 = 29;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
////////////////////////////weight sensor//////////////////////////
#define DT A0
#define SCK A1
#define sw 22
long sample=0;
float val=0; 
long count=0;

//#define rx 10
//#define tx 9
//SoftwareSerial com(rx,tx)
/////////////////////////////////gps/////////////////////////////////
TinyGPS gps;
/////////////////////////////blynk///////////////////////////////
char auth[] = "BNDCcJKaKSfnTrEdfiq4OnXlVzpRl_zC";
WidgetLED ledWarning(V1); //register to virtual pin 1  led1.off(); led1.on();
WidgetLED ledSuccess(V2); //register to virtual pin 2
WidgetTerminal terminal(V0);
#define lock 23
int weight=0;
float llat=0;
float llon=0;

void setup() {
  
  
  Serial.begin(9600);
  Serial1.begin(9600);
  
  
  //////////////////////////////////////weight snsor///////////////////////
  pinMode(DT, INPUT);
  pinMode(SCK, OUTPUT);
  pinMode(sw, INPUT_PULLUP);//set sw to default 1
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("    Weight ");
  lcd.setCursor(0,1);
  lcd.print(" Measurement ");
  delay(1000);
  lcd.clear();
  calibrate();//calibrating the weight scale
  
  //////////////////////////gps formula testing/////////////////////////////
//  Serial1.print("Expected answer :");
//  Serial1.print("1350");
//  Serial1.print(" Answer calc: ");
//  Serial1.println(getDistanceFromLatLonInKm(10,12,3,2));
//  
//  Serial1.print("Expected answer :");
//  Serial1.print("566");
//  Serial1.print(" Answer calc: ");
//  Serial1.println(getDistanceFromLatLonInKm(8,5,13,6));
//  
//  Serial1.print("Expected answer :");
//  Serial1.print("248");
//  Serial1.print(" Answer calc: ");
//  Serial1.println(getDistanceFromLatLonInKm(4,3,5,1));
  
  ///////////////////////////////////////blynk//////////////////////////
  Blynk.begin(auth, Serial);
  pinMode(lock,OUTPUT);
  digitalWrite(lock,LOW);
  terminal.clear();
  ledWarning.off();
  ledSuccess.off();
  terminal.println(F("Blynk Device started"));
  getDataFromTerminal();
  
}

void loop() {
////////////////////////////////////weight sensor/////////////////////////////////////
  count= readCount();
  int w=((count-sample)/val);
  Serial1.print("weight:");
  Serial1.print((int)w);
  Serial1.println(" g");
  lcd.setCursor(0,0);
  lcd.print("Weight : ");
  lcd.print(w);
  lcd.print(" g");
  
  //recalibrate push the button
  if(digitalRead(sw)==0)
  {
    val=0;
    sample=0;
    w=0;
    count=0;
    calibrate();
  }

/////////////////////////////////////////gps//////////////////////////////////////
  //Serial1.print(millis());
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  float flat=0, flon=0;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial1.available())
    {
      char c =Serial1.read();
      if (gps.encode(c)) 
        newData = true;  
    }
  }
  
  if (newData)      //If newData is true
  {
    
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    delay(300);
    Serial1.print("Latitude = ");
    Serial1.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial1.print(" Longitude = ");
    Serial1.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(200);
    Serial1.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    
    //lcd.setCursor(0,1);
    //lcd.print("LAT:");
    //lcd.print(flat,1);
    //lcd.print(" LON:");
    //lcd.print(flon,1);
    delay(100);
 }
/////////////////////////////////blynk//////////////////////////////////////////
  Blynk.run();
//////////////////////////////////algo////////////////////////////////////////
//we have weight and the gps coordinates now we have to see if there is any error
  
  if(abs(w-weight) > 10){
    //there is a difference of 10 gram in weight
    sendEmailNotification(0,w,flat,flon);
    ledWarning.on();
    String msg="Current weight:"+String(weight)+"\nLongitude: "+String(llon)+" Latitude:"+String(llat);
    terminal.println(msg);
    if(digitalRead(lock)==0){
      terminal.println(msg);
      terminal.println("Press on lock to initiate lockdown ");
    }
    terminal.flush();
  }
  else{
    ledWarning.off();
  }
  
  Serial1.println("Diatance from destination"+ String(getDistanceFromLatLonInKm(flat,flon,llat,llon)));
  if((getDistanceFromLatLonInKm(flat,flon,llat,llon)<1)&&(flat!=0)&&(flon!=0)){
    //distance is less than 1 km
    sendEmailNotification(1,w,flat,flon);
    ledSuccess.on();
    String msg="Current weight:"+String(weight)+"\nLongitude: "+String(llon)+" Latitude:"+String(llat);
    terminal.println(msg);
    terminal.println("Successfully delivered.");
    terminal.flush();
    exit(0);
  }
  else{
    ledSuccess.off();
  }
  
}
float getDistanceFromLatLonInKm(float lat1,float lon1,float lat2,float lon2) {
  float R = 6371; // Radius of the earth in km
  float dLat = deg2rad(lat2-lat1);  // deg2rad below
  float dLon = deg2rad(lon2-lon1); 
  float a = 
    sin(dLat/2) * sin(dLat/2) +
    cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * 
    sin(dLon/2) * sin(dLon/2); 
  float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  float d = R * c; // Distance in km
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Distance:");
  lcd.print(d);
  delay(100);
  return d;
}

float deg2rad(float deg) {
  return deg * (PI/180);
}
//float getCoordinateDist(float lat1,float lon1,float lat2,float lon2){
//  ACOS(SIN(PI()*[Lat_start]/180.0)*SIN(PI()*[Lat_end]/180.0)+COS(PI()*[Lat_start]/180.0)*COS(PI()*[Lat_end]/180.0)*COS(PI()*[Long_start]/180.0-PI()*[Long_end]/180.0))*6378
//  int r = 6371 ;//radius of Earth (KM)
//  float p = 0.017453292519943295;  //Pi/180
//  float a = 0.5 - cos((lat2-lat1)*p)/2 + cos(lat1*p)*cos(lat2*p) * (1-cos((lon2-lon1)*p)) / 2;
//  float d = 2 * r * asin(sqrt(a)); //2*R*asin
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Distance:")
//  lcd.setCursor(0,1);
//  lcd.print(d);
//  delay(100);
//  return d;
//}
/////////////////////////////////blynk//////////////////////////////////////////
void getDataFromTerminal(){
  bool flag1=true;
  bool flag2=true;
  bool flag3=true;
  while(true){
    Blynk.run();
    if(flag1){
      terminal.println(F("Enter the weight of sample in gram: "));
      terminal.flush();
      flag1=false;  
    }
    if(weight==0){continue;}
    if(flag2){
      terminal.println(F("Enter the Longitude of Destination : "));
      terminal.flush();
      flag2=false;  
    }
    if(llon==0){continue;}
    if(flag3){
      terminal.println(F("Enter the Latitude of Destination : "));
      terminal.flush();
      flag3=false;  
    }
    if(llat==0){continue;}
    String msg="Required weight of gold:"+String(weight)+"\nLongitude: "+String(llon)+" Latitude:"+String(llat);
    terminal.println(msg);
    terminal.flush();
    break;
  }
  
}
void sendEmailNotification(int mode,int mweight,float mflat,float mflon){
  String msg="Current weight:"+String(mweight)+"\n Longitude: "+String(mflon)+" Latitude:"+String(mflat);
  if(mode==0){
    Blynk.email("Warning Notification", msg);  
  }
  else{
    Blynk.email("Success", msg);
  }
  
}
BLYNK_WRITE(V0)
{
  if(weight==0){
    weight=atoi(param.asStr());
  }
  else{
    if(llon==0){
      String x=param.asStr();
      llon=x.toFloat();
    }
    else{
      String x=param.asStr();
      llat=x.toFloat();
    }
  }
}
/////////////////////////////weight sensor///////////////////////////////////////
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
//    Serial1.println(count);
  }
  sample/=100;
  Serial1.print("Avg reading without any weight :");
  Serial1.println(sample);//basically weight due to atmosphere
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Put 100g & push button");
  while(digitalRead(sw)!=0){
    //Waiting for 100gm to be put and push button to be pressed
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
  Serial1.print("Avg of value of voltage per gm :");
//  lcd.setCursor(0,1);
  Serial1.println(val);//basically weight due to atmosphere
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
