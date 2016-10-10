// Requires the RTC library from Adafruit
// I believe I got it from the Adafruit or Arduino site.
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
void setup () {
Serial.begin(9600);
Wire.begin();
RTC.begin();
int dummy1 = 0; // these were added due to a bug in the Arduino IDE.
int dummy2 = 0; // Sketches generate a error, without any info as to the cause/type
int dummy3 = 0; // of error. Someone figured out that by adding 4 or more dummy vars.
int dummy4 = 0; // it allowed the sketch to load. I had this problem so add these to all
// of my sketches and haven’t had that error pop up again. (Windows XPsp3).

if (! RTC.isrunning()) {
  Serial.println("RTC is NOT running!");
  // following line sets the RTC to the date & time this sketch was compiled
  // uncomment it & upload to set the time, date and start run the RTC!
  RTC.adjust(DateTime(__DATE__, __TIME__));
} else {
  Serial.print("RTC IS running! Current time is: ");
  // fetch the time
  printCurrentTime();
}
  Serial.println("Type any character to update time to host's time");
  while (!Serial.available());
  RTC.adjust(DateTime(__DATE__, __TIME__));
  printCurrentTime();
}
void loop(void){
// nothing
}
void printCurrentTime(void){
    DateTime now;
  now = RTC.now();
  Serial.print(now.unixtime()); // seconds since 1/1/1970
  Serial.print(", ");
  Serial.print('"');
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print('"');
}


