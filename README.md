# Gringotts Wizarding Bank

 Basic security system using IOT

#### Features

- A cart that carries the gold while monitoring its weight
- The GPS location of the cart is sent to the security office as soon
  as the weight of the gold alters
- On reaching the destination, a confirmatory signal is sent to the
  security office.
- Locking/alarm system in case of disturbance in the gold cart.
- Control over cart route/doors using tools like Blynk.

#### Working/TimeLine

Start VSPE . Create a new connection and pair COM1 and COM4.

Connect to blynk server (blynk-ser.bat -c com1 -p 8442) , do check the the ports in blynk-ser are COM1.

Start the simulation .

Run the project in blynk app.

Follow the instructions in terminal and LCD respectively. 

1. Put 100g on weigh scale the reading of load cell must change respectively and push the button and wait until tolld.
2. Put the actual weight on the scale.
3. Enter weight of sample in gram on blynk app.
4. Set the latitude and longitude of destination .

We are ready to go .

The terminal will keep on printing the current weight and location of vehicle after certain intervals.

#### Technical Features 

- Automatic calibration to atmospheric pressure by calculating reading change in read before and after placing 100g
- HX711 for converting analog to digital value
- Setting up latitude and longitude on each journey
- Email notification on too far from destination and LED blinking.
- Blink LED on successfully reaching destination.

#### Circuits and connections

![image](https://user-images.githubusercontent.com/56964828/126814541-050f4ea2-359f-4ab4-bc2c-2054c47a23af.png)

![image](https://user-images.githubusercontent.com/56964828/126814652-56e64ca0-0279-40fd-bf08-1d932be90b22.png)

Blynk app 

Button -> Digital Pin 23

2 LED's -> Virtual Pin V1, V2

Terminal -> V0

![image](https://user-images.githubusercontent.com/56964828/129022980-8c28e56c-bc0c-4b45-9d51-c11eee4ab32e.png)
![image](https://user-images.githubusercontent.com/56964828/129022994-7f8e99d6-8377-44a4-ba81-57241be5bcc2.png)

#### Installation Instructions : 

Remove read only permission on Proteus , see youtube video on how to do that

#### Software used :

- Proteus_Professional_8.9_SP2_Build_28501
- arduino-1.8.15-windows
- SetupVSPE
- Blynk 

#### Libraries Imported :

- Adrduino Library (Extract Arduino library rar file and copy all the files C:\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\DATA\LIBRARY )
- Download Blynk and add it to arduino libraries
- Add additional Url in FIle>Preferences : http://arduino.esp8266.com/stable/package_esp8266com_index.json

#### Other Instructions :

- In Arduino IDE , go to File and Compilation checkbox must be checked .

- Install libraries in Tools>Libraries . TinyGPS , Liquid Crystal

- Connecting to Blynk Server

  vspe-pairing start(COM4(proteus-comimp),COM1-blynk)
  Start blnk.ser with command in command prompt
  blynk-ser.bat -c com1 -p 8442
  Start proteus simulation

- Change Board to Arduino Mega in Tools > Boards
- Sketch > Export Compiled Binary , is used to save hex file at location of file
- change auth in code according to your app in blynk , you will find it in setting of your project , also your board should be Arduino Mega
- In COMPIMP set port as COM4 and set baud rate to 9600.

Always feel free to check the samples to see step by step how things become as they are .

