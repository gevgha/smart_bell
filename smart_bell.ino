#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку
#include <Wire.h>
#include "RTClib.h"
#define relayPin 8            // Ռելեյի պինը
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)
String daysOfWeek [] = {"Sun.","Mon.","Tue.","Wed.","Thu.","Fri.","Sat.",};
String bellTime [] = {"9:00","9:45","9:50","10:35","10:40","11:25","11:35","12:20","12:25","13:10","13:15","14:00","14:05","14:50"};
byte bellIndex = 0;
RTC_DS3231 rtc;
byte bell_duration = 5;
byte  dow , hour , minute, sec;
byte compileSecond = 7;

void setup(){
    Serial.begin(9600);               // Инициализируем вывод данных на монитор серийного порта, со скоростью 9600 бод
    pinMode(relayPin, OUTPUT); 
    rtc.begin();
   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));                
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
   hour = now.hour();
   minute = now.minute();
   sec = now.second()+compileSecond;
   if(sec > 59){
   sec = sec - 60;
   }
}

void calculateTime(){
    delay(999);
    sec++;
    if (sec > 59){
       minute++;
      sec = 0;
    }
    if (minute > 59) {
      hour++;
      minute = 0;
    }
    if (hour > 23){
      hour = 0;
    }
}

void soundingBell(){
  if(dow!=6 || dow!=7){    
       if(hour == 9 && minute == 0 && sec==0){relayStates();}
        if(hour == 9 && minute == 45 && sec == 0){relayStates();} 
        if(hour == 9 && minute == 50 && sec == 0){relayStates();} 
        if(hour == 10 && minute == 35 && sec == 0){relayStates();}
        if(hour == 10 && minute == 40 && sec == 0){relayStates();}
        if(hour == 11 && minute == 25 && sec == 0){relayStates();}
        if(hour == 11 && minute == 35 && sec == 0){ relayStates();}
        if(hour == 12 && minute == 20 && sec == 0){relayStates();} 
        if(hour == 12 && minute == 25 && sec == 0){relayStates();}
        if(hour == 13 && minute == 10 && sec == 0){relayStates();}
        if(hour == 13 && minute == 15 && sec == 0){relayStates();}
        if(hour == 14 && minute == 00 && sec == 0){ relayStates();}
        if(hour == 14 && minute == 05 && sec == 0){relayStates();}
        if(hour == 14 && minute == 50 && sec == 0){relayStates();}
  }
   if(minute == 0&& sec == 0){ relayStates();}
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
   if(minute< 10){
    minuteS = String(0)+ String(minute);
   }else{
    minuteS = String( minute);
   }
   if (sec<10){
    secondS = String(0)+ String(sec);
   }else {
    secondS = String(sec);
   }

   
  String date = (String(hour) +":" + minuteS + ":" + secondS+"    "+daysOfWeek[dow]);
  Serial.println(date);
 // lcd.clear();
 // lcd.setCursor(0, 0);              // Устанавливаем курсор в начало 1 строки
 // lcd.print(date);       // Выводим текст
 // lcd.setCursor(0, 1);              // Устанавливаем курсор в начало 2 строки
 // lcd.print(bellTime[bellIndex]);         // Выводим текст
}

void relayOn(){
 digitalWrite(relayPin,HIGH);  
}  

void relayOff(){
 digitalWrite(relayPin,LOW);  
}

inline void Reset() {
  if(hour == 8 && minute == 30 && sec == 0){
    delay(50000); 
    asm("JMP 0");
  }
}
