# CarMonitor
An Arduino project for logging pre-OBD car vitals (batt voltage, air temp, coolant temp, &amp; map pressure).


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
