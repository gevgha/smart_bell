#include <TimeLib.h> //Ավելացնել ժամանակի գրադարանը

//#include <LiquidCrystal.h>  //Ավելացնել էկրանի գրադարանը
#include <Wire.h>
#include "RTClib.h"  //Ավելացնել Իրական ժամանակի գրադարանը
int  relayPin =  4;            // Ռելեյի պինը
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)
String daysOfWeek [] = {"Sun.","Mon.","Tue.","Wed.","Thu.","Fri.","Sat.",};
String bellTime [] = {"9:00","9:45","9:50","10:35","10:40","11:25","11:35","12:20","12:25","13:10","13:15","14:00","14:05","14:50"};
int rests[] = {10,15,10,5,5,5}; //ընդմիջումները 1, 2, 3, 4, 5, 6 դասերից հետո
int lessonsDuration[] = {45,45,45,45,45,45,45}; //Դասերի տևողույունը 1, 2, 3, 4, 5, 6, 7
byte bellIndex = 0;
RTC_DS3231 rtc;
byte bell_duration = 8;
byte  dow , hourR , minuteR, sec;
byte compileSecond = 15;


void setup(){
    Serial.begin(9600);               // Инициализируем вывод данных на монитор серийного порта, со скоростью 9600 бод
    pinMode(relayPin, OUTPUT); 
    
    rtc.begin();
   //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));                
//  clock.setDateTime(2016, 9, 15, 0, 0, 0);              // Установка времени вручную (Год, Месяц, День, Час, Минута, Секунда)
//  setAlarm1(Дата или день, Час, Минута, Секунда, Режим)
    readTime();
   // lcd.begin(16, 2);                  // Задаем размерность экрана
}

void loop(){
  Reset();
  calculateTime();
  printData();                  
  //soundingBellTest();
  soundingBell();                                           
}

void readTime(){
   DateTime now = rtc.now();
   dow = now.dayOfTheWeek();
   hourR = now.hour();
   minuteR = now.minute();
   sec = now.second()+compileSecond;
   if(sec > 59){
   sec = sec - 60;
   }
}

void calculateTime(){
    delay(995);
    sec++;
    if (sec > 59){
       minuteR++;
      sec = 0;
    }
    if (minuteR > 59) {
      hourR++;
      minuteR = 0;
    }
    if (hourR > 23){
      hourR = 0;
    }
}

void soundingBell(){
       //9։00
       setTime(9,0,0,1,1,1970); 
       if(dow!=0 && dow!=6){    }
      
       for(int i = 0; i <  sizeof(lessonsDuration)/2; i++){
         if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
         changeTime(lessonsDuration[i]);
         if(i < sizeof(rests)/2){
           if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
            changeTime(rests[i]);
         }
       }
       
       if(minuteR == 0 && sec == 0){relayStates();}
       if(minuteR == 30 && sec == 0){relayStates();}
}

void changeTime(int min){
 setTime(hour(), minute()+ min ,0,1,1,1970);
 // printDigitalClockDisplay();
}

void relayStates(){
   relayOn();
   delay((bell_duration * 1000));   //թիվը վերածում է վրկ․
   sec = sec + bell_duration;
   relayOff();
}

void printData(){
   String minuteS = "";
   String secondS = "";
   if(minuteR< 10){
    minuteS = String(0)+ String(minuteR);
   }else{
    minuteS = String( minuteR);
   }
   if (sec<10){
    secondS = String(0)+ String(sec);
   }else {
    secondS = String(sec);
   }

   
  String date = (String(hourR) +":" + minuteS + ":" + secondS+"    "+daysOfWeek[dow]);
  Serial.println(date);
}

void relayOn(){
 digitalWrite(relayPin,HIGH);  
}  

void relayOff(){
 digitalWrite(relayPin,LOW);  
}

inline void Reset() {
  if(hourR == 8 && minuteR == 30 && sec == 0){
    delay(50000); 
    asm("JMP 0");
  }
}

void printDigitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.println(); 
}
