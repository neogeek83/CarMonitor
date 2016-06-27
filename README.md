# CarMonitor
An Arduino project for logging pre-OBD car vitals (batt voltage, air temp, coolant temp, &amp; map pressure). Meant to be used with an Arduino Duemilanove

##Project Sketches
 * CarMonitor
   Brings all the below projects together
   
##Supporting Sketches
 * ImpedanceTester
   Code specific to create an Ohm Meter
 * SDWriter
   Project for bringing up the SDCard writer. This expects an SDcard writter /w RTC (set the clock using the below project prior to using this one)
 * SetSDCardRTCTime
   Set the time for the SDCard writer uses SDcard read/write shield /w RTC (something like these: http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2055845.m570.l1313.TR0.TRC0.H0.Xsdcard+arduino+rtc.TRS0&_nkw=sdcard+arduino+rtc&_sacat=0)

###Sensors

Diesel Truck Coolant sensor - FZAF-12A648-A4
 * ~65 degrees => 31 K Ohms
 * finger warming, ~85-90degrees =>28kOhms

BMW External Air Temperature Sensor  - Yellow base - (part #1 383 204)
 * 3.5kohms ~65degrees 

BMW External black air sensor
 3066.1 @ 98.5f
 7355.93 @ 61.5f
 5260 @ 75f


###TODO
 * wire in hall effect sensor to car
 * drill hole and mount water temp sensor
 * wire in ACC voltage sensor
 * wire in Air temp sensor
 * run wire through heat shield
 * wire up molex connector for fast disconnect of Arduino
 * pretty up arduino code
 * take pictures of setup and add to this readme
 * add a MAP sensor to system
 * add secondary voltage sensor as alternate to hall sensor(connected to (-) coil and ACC) 
