/*
  DS3231: Real-Time Clock.
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-DS3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include "RTClib.h"
#define relayPin 4            // Ռելեյի պինը
RTC_DS3231 rtc;
byte bell_duration = 5;
byte  dow , hour , minute, sec;
byte compileSecond = 9;

void setup(){
Serial.begin(9600);               // Инициализируем вывод данных на монитор серийного порта, со скоростью 9600 бод
pinMode(relayPin, OUTPUT); 
rtc.begin();
 // clock.setDateTime(__DATE__, __TIME__);                  // Устанавливаем время на часах, основываясь на времени компиляции скетча
//  clock.setDateTime(2016, 9, 15, 0, 0, 0);              // Установка времени вручную (Год, Месяц, День, Час, Минута, Секунда)
//  setAlarm1(Дата или день, Час, Минута, Секунда, Режим)
   readTime();
}

void loop(){
  Reset();
  calculateTime();
  printData();                  
  soundingBellTest();
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
    delay(1000);
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

void soundingBellTest(){   
     if(hour == 18 && minute == 52 && sec==0){
        relayStates();
     } else if(hour == 18 && minute == 54 && sec == 0){ 
        relayStates();
     } else if(hour == 18 && minute == 59 && sec == 0){ 
        relayStates();
     } else if(hour == 18 && minute == 55 && sec == 0){ 
        relayStates();
     } else if(hour == 19 && minute == 10 && sec == 0){ 
        relayStates();
     }
}

void soundingBell(){
  if(dow!=6 || dow!=7){    
     if(hour == 9){
        if(hour == 9 && minute == 0 && sec==0){
           relayStates();
        } else if(hour == 9 && minute == 45 && sec == 0){ 
           relayStates();
        } else if(hour == 9 && minute == 50 && sec == 0){ 
           relayStates();
        }
     }else if (hour == 10){
        if(hour == 10 && minute == 35 && sec == 0){ 
           relayStates();
        }else if(hour == 10 && minute == 40 && sec == 0){
           relayStates();
        }
     }else if (hour == 11){
        if(hour == 11 && minute == 25 && sec == 0){
           relayStates();
        }else if(hour == 11 && minute == 35 && sec == 0){
           relayStates();
        }
     }else if(hour == 12){
        if(hour == 12 && minute == 20 && sec == 0){
           relayStates();
        }else if(hour == 12 && minute == 25 && sec == 0){
           relayStates();
        }
     }else if(hour == 13){
        if(hour == 13 && minute == 10 && sec == 0){
          relayStates();
        }else if(hour == 13 && minute == 15 && sec == 0){
          relayStates();
        }
     }else if(hour == 14){
         if(hour == 14 && minute == 00 && sec == 0){ 
           relayStates();
         }else if(hour == 14 && minute == 05 && sec == 0){
           relayStates();
         }else if(hour == 14 && minute == 50 && sec == 0){
           relayStates();
         }
     }
  }
}

void relayStates(){
   relayOn();
   delay((bell_duration * 1000));   //թիվը վերածում է վրկ․
   sec = sec + bell_duration;
   relayOff();
}

void printData(){
      Serial.print("dayOfTheWeek");
      Serial.print(dow);
      Serial.println();
      Serial.print(hour);    
      Serial.print(":");
      Serial.print(minute);
      Serial.print(":");
      Serial.print(sec);
      Serial.print(" ");
      Serial.println();
}

void relayOn(){
 digitalWrite(relayPin,HIGH);  
}  

void relayOff(){
 digitalWrite(relayPin,LOW);  
}

inline void Reset() {
  if(hour==8 && minute==30 && sec==0){
    delay(50000); 
    asm("JMP 0");
  }
}
