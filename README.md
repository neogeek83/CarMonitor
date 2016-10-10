# CarMonitor
An Arduino project for logging pre-OBD car vitals (batt voltage, air temp, coolant temp, &amp; map pressure). Meant to be used with an Arduino Duemilanove

##Dependencies
  * Arduino Libraries
    * RTCLib
    * SD (built-in now I think)
    * Wire (built-in now I think)

##Project Sketches
 * CarMonitor - Brings all the below projects together
   
##Supporting Sketches
 * ImpedanceTester - Code specific to create an Ohm Meter
 * SDWriter - Project for bringing up the SDCard writer. This expects an SDcard writter /w RTC (set the clock using the below project prior to using this one)
 * SetSDCardRTCTime - Set the time for the SDCard writer uses SDcard read/write shield /w RTC (something like these: http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2055845.m570.l1313.TR0.TRC0.H0.Xsdcard+arduino+rtc.TRS0&_nkw=sdcard+arduino+rtc&_sacat=0)

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

###WIRING
  * https://goo.gl/photos/Le24ZwGX4rxnEHM88 
  * Harness (Pin 1 on breadboard is closest to Arduino):
    *  1 blue - intake temperature
	*  2 b /w - intake temp (-)
	*  3 orange - coil voltage
	*  4 o /w   - coil voltage (-)
	*  5 brown - 12V system
	*  6 b / w - 12V system (-)
	*  7 green - coolant temperature sensor
	*  8 g / w - coolant temperature sensor (-)
  * Arduino Pins:
    * A0 - Air Sensor (Black) (10k)
	* A1 - ~ (10.3k)
	* A2 - ~ (10.1k)
	* A3 - Voltmeter (32.7k)
	* A4 - Air Sensor (Yellow) (10.02k)
	* A5 - Water Sensor (10k)
	* D2 - hall effect sensor

###TODO
  * Troubleshoot wiring harness pins 7/8 - why does connecting freeze app?
	* Tried swapping with A1, A2, A4, same effect
  * Recalibrate/troubleshoot Intake Air Temp(pin 1 and 2) and calibrate water sensor
  * Wire up breadboard to wiring harness
  * wire in hall effect sensor to car
  * pretty up arduino code
  * take pictures of setup and add to this readme
  * add a MAP sensor to system
  * add secondary voltage sensor as alternate to hall sensor(connected to (-) coil and ACC) 
