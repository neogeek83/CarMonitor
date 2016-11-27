# CarMonitor
An Arduino project for logging pre-OBD car vitals (timestamp, batt voltage, air temp, coolant temp, &amp; HAL sensor for RPM) to an SD card for review later on PC. Can also be used for real-time monitoring. Tested with Arduino Duemilanove and Uno.

<img src="https://github.com/neogeek83/CarMonitor/blob/master/docs/wiring%20harness/20161107_201841_HDR.jpg?raw=true" />

Sample real output can be found here (read from a '82 Triumph Spitfire): CarMonitor/CarMonitor/sensor_readings/LOGGER05_baseline_issue_didnt_occur.CSV

## Backstory
As an excuse to learn more about Arduino programming and cars, my brother an I decided to build a logger to help us troubleshoot an intermittent problem with our parent's '82 Spitfire(pre-ODB days). We wanted something that could log every run of the car so we could leave it in there and it'd just go( powered the Arduino from an cigarette lighter->USB charger). Every time the car is turned on, a new log file would be created (stops recording after 999 engine runs). This way we could have data on what was happening after the fact when the issue occurred. This project is the result, and it worked great we were able to figure out the problem and validate the fix (turned out to be an electronic ignition under-voltage issue)! If anyone else plays with it and finds it useful(or doesn't), open an issue and let me know how it went for you!

##Dependencies
### Hardware
  * Arduino Duemilanove or Uno (others probably work, but have tested these 2)
  * SDCard /w RTC shield
  * Sensors (various supported, most car sensors are resistive, will just need to re-calibrate if different from ones listed below and in docs/)

### Software
  * Arduino Libraries
    * RTCLib
    * SD (built-in now I think)
    * Wire (built-in now I think)

##Quick Start
 * Clone repo locally
 * Attach SDCard shield to Arduino baseboard, calibrate SDCard RTC (see SetSDCardRTCTime project), format SDCard on PC (FAT32)
 * Update 'ECHO_TO_SERIAL' and  'WAIT_TO_START' in CarMonitor.ino (both to 1 while connected to computer for testing, both to 0 for production)
 * Wire up some sensors (off car, 1 at a time, to start probably best)<br>
<img height="128" width="304" src="https://github.com/neogeek83/CarMonitor/blob/master/docs/sensor_wiring.png?raw=true" />
 * Calibrate sensors
   * Update 'float R1[6]=' in 'CarMonitor.ino' for actual resistors used on breadboard (use multimeter to check real values)
   * Get raw readings when wired in and enter into docs/Sensor_Calibration.xlsx
   * Update 'readAnalogs(bool outputIt)' in 'CarMonitor.ino' using Slope and x-intercept from spreadsheet (graph will show if linear)
 * That's it, you should be good to go, log away!

##Project Sketches
 * CarMonitor - Brings all the below projects together
   
##Supporting Sketches
 * ImpedanceTester - Code specific to create an Ohm Meter
 * SDWriter - Project for bringing up the SDCard writer. This expects an SDcard writter /w RTC (set the clock using the below project prior to using this one)
 * SetSDCardRTCTime - Set the time for the SDCard writer uses SDcard read/write shield /w RTC (something like these: http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2055845.m570.l1313.TR0.TRC0.H0.Xsdcard+arduino+rtc.TRS0&_nkw=sdcard+arduino+rtc&_sacat=0)

###Sensors( see docs/Sensor Readings.xlsx for more)

  * HAL Sensor: 
    * Numbers printed on device: 3144 601
    * Specs: http://www.elecrow.com/download/A3141-2-3-4-Datasheet.pdf
    * Pinout: (1 is left when looking at printed letters).
      * Pin 1 = Vcc
      * Pin 2 = GND
      * Pin 3 = output (voltage varies)

###WIRING
  * Here's the full diagram for the project:<br>
  <img src="https://easyeda.com/normal/Arduino_Uno_Sheild-de7a6aff0f0b4fc9a0959b22d81b2400" /> pdf for printing at docs/Arduino_Schematic.pdf
  * https://goo.gl/photos/Le24ZwGX4rxnEHM88 
  * Harness #1 (Pin 1 on breadboard is closest to Arduino):
    *  1 blue - intake temperature
    *  2 b /w - intake temp (-)
    *  3 orange - coil voltage (unused)
    *  4 o /w   - coil voltage (-)(unused)
    *  5 brown - 12V system
    *  6 b / w - 12V system (-)
    *  7 green - coolant temperature sensor
    *  8 g / w - coolant temperature sensor (-) (disconnected on engine side)

  * Harness #2 (Pin 1 on breadboard is closest to Arduino):
    *  1 blue - unused
    *  2 b /w - unused
    *  3 orange - unused
    *  4 o /w   - unused
    *  5 brown - HALL GND 
    *  6 b / w - HALL 5Vcc
    *  7 green - HALL Sensor (pulls to GND when magnet S pole is detected)
    *  8 g / w - unused
	
  * Arduino Pins:
    * A0 - Air Sensor (Black) (10k)
    * A1 - ~ (10.3k)
    * A2 - ~ (10.1k)
    * A3 - Voltmeter (32.7k)
    * A4 - Air Sensor (Yellow) (10.02k)
    * A5 - Water Sensor (10k)
    * D2 - hall effect sensor

###TODO

  * Recalibrate Intake Air Temp(pin 1 and 2) 
  * pretty up arduino code
  * take pictures of setup and add to this readme
  * Create 'event' button to board and in software
  * Add H20 temp sensor(current one isn't going to work due to 12v power being sent to it--will fry the Arduino input PIN)
  * Add a MAP sensor to system
  * Add Coil Voltage Sensor
