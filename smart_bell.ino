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
byte compileSecond = 10;


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
    delay(999);
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
  
       //Առաջին դասի սկիզբ 9։00
       if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
       printDigitalClockDisplay(); 
       
       //Սահմանել առաջին դասի ավարտը 9։0 + 45
       setTime(hour(), minute()+ lessonsDuration[0] ,0,1,1,1970); 
       if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
       printDigitalClockDisplay();
       
       // 9 ։ 45 + 5
       setTime(hour(), minute()+ rests[0] ,0,1,1,1970); 
       //Երկրորդ դասի սկիզբ 9 ։ 50
       if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
       printDigitalClockDisplay();
       
        //9 ։ 50 + 45
        setTime(hour(), minute()+ lessonsDuration[1] ,0,1,1,1970); 
        //Երկրորդ դասի ավարտ 10 ։ 35 
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();

        //10 ։ 35 + 5
        setTime(hour(), minute()+ rests[1] ,0,1,1,1970); 
        //Երրորդ դասի սկիզբ 10 ։ 40 
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();

        
        //10 ։ 40+ 45
        setTime(hour(), minute()+ lessonsDuration[2] ,0,1,1,1970); 
        //Երրորդ դասի ավարտ 11 ։ 25 
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();

        //11:25+ 5
        setTime(hour(), minute()+ rests[2] ,0,1,1,1970); 
        //չորորդ դասի սկիզբ 
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();


        //11։30 + 45
        setTime(hour(), minute()+ lessonsDuration[3] ,0,1,1,1970);
        //չորորդ դասի ավարտ 12։15
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();


        //12։15 + 5
        setTime(hour(), minute()+ rests[3] ,0,1,1,1970); 
        //հինգերորդ դասի սկիզբ 12։20
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();


        //12։20 + 45
        setTime(hour(), minute()+ lessonsDuration[4] ,0,1,1,1970);
        //հինգերորդ դասի ավարտ 13։05
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();


        //13։05 + 5
        setTime(hour(), minute()+ rests[4] ,0,1,1,1970); 
        //վեցերորդ դասի սկիզբ 13։10
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();


        //13։10 + 45
        setTime(hour(), minute()+ lessonsDuration[5] ,0,1,1,1970);
        //վեցերորդ դասի ավարտ 13։55
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();


        //13։55 + 5
        setTime(hour(), minute()+ rests[5] ,0,1,1,1970); 
        //յոթերորդ դասի սկիզբ 14։00
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();


        //14։00 + 45
        setTime(hour(), minute()+ lessonsDuration[6] ,0,1,1,1970);
        //յոթերորդ դասի ավարտ 14։45
        if(hourR == hour() && minuteR == minute() && sec == second()){relayStates();}
        printDigitalClockDisplay();

        
               

  
   if(minuteR == 0 && sec == 0){relayStates();}
   while(true){}
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
