#include <SD.h>
#include <Wire.h>
#include "RTClib.h" //Requires RTClib be installed (Sketch->Include Library->Manage Libraries...->search for RTCLib->install


#define ECHO_TO_SERIAL   1 // echo data to serial port
#define WAIT_TO_START    1 // Wait for serial input in setup()
#define RAW_OUT          1 // if 1, will output to serial the raw analog pin value readings (only works with ECHO_TO_SERIAL 1)

// how many milliseconds between grabbing data and logging it. 1000 ms is once a second
#define LOG_INTERVAL  1000 // mills between entries (reduce to take more/faster data)

// how many milliseconds before writing the logged data permanently to disk
// set it to the LOG_INTERVAL to write each time (safest)
// set it to 10*LOG_INTERVAL to write all data every 10 datareads, you could lose up to 
// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1000 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

String LOGFILE_HEADER = "millis,epoch,datetime,blackair,yellowair,watertemp,12v,rpm";

RTC_DS1307 RTC; // define the Real Time Clock object


// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

// the logging file
File logfile;

void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  while(1);
}


// -- hall sensor

 //DIGITAL PIN 2 for the hall sensor input. 
 volatile byte half_revolutions;
 unsigned int rpm;
 unsigned long timeold;

 // -- end hall sensor



// Sensor reader
int analogPins[6]= {0,1,2,3,4,5};
int raw[6]= {0};
int Vin= 5;
float Vout[6]= {0};
float R1[6]= {10000,10300,10100,32700,10020,10000}; //in ohms
float R2[6]= {0};
float buffer[6]= {0};

void setup() {
  Serial.begin(9600);
  Serial.println();

// -- hall sensor
   digitalWrite(2, HIGH);
   attachInterrupt(0, rpm_fun, RISING);

   half_revolutions = 0;
   rpm = 0;
   timeold = 0;
// -- end hall sensor
  
#if WAIT_TO_START
  Serial.println("Type any character to start");
  while (!Serial.available());
#endif //WAIT_TO_START

  // initialize the SD card
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    error((char*)"Card failed, or not present");
  }
  Serial.println("card initialized.");
  
  // create a new file
  uint16_t MAX_NUM_FILES = 1000;
  char filename[12];
  for (uint16_t i = 0; i < MAX_NUM_FILES; i++) {
    sprintf(filename, "log-%03d.csv", i);
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    } else if (i==(MAX_NUM_FILES-1)){
      error((char*)"Max number of files reached, download logs from SDCard or move off SD root.");
    }
  }
  
  if (! logfile) {
    error((char*)"Couldn't create file:");
    Serial.println(filename);
  }
  
  Serial.print("Logging to: ");
  Serial.println(filename);

  // connect to RTC
  Wire.begin();  
  if (!RTC.begin()) {
    logfile.println("RTC failed");
#if ECHO_TO_SERIAL
    Serial.println("RTC failed");
#endif  //ECHO_TO_SERIAL
  }
  

  logfile.println(LOGFILE_HEADER);    
#if ECHO_TO_SERIAL
  Serial.println(LOGFILE_HEADER);
#endif //ECHO_TO_SERIAL
 
  // If you want to set the aref to something other than 5v
//  analogReference(EXTERNAL);
}

void readAnalogs(bool outputIt){

  //Read in all 6 inputs, no way to read multiple at once, 
  // so do it one at a time
  for (int i=0;i<6;i++){
    raw[i]=analogRead(analogPins[i]);
    delay(10);
    if(raw[i]) {
      buffer[i]= raw[i] * Vin;
      Vout[i]= (buffer[i])/1024.0;
      buffer[i]= (Vin/Vout[i]) -1;
      R2[i]= R1[i] * buffer[i];
      if (outputIt){

        // BMW Black Air Sensor
        if (i==0){
          R2[i]=-.00864*R2[i]+123.5043;
          Serial.print(", IAT= ");
          Serial.print(R2[i]);
        }
        // Volt Meter
        else if (i==3){
          R2[i]=raw[i]/59.046f;
          Serial.print(", battV= ");
          Serial.print(R2[i]);
        }
        // BMW Yellow Air Sensor
        else if (i==4){
          R2[i]=-.11244*R2[i]+241.3669;
          Serial.print(", Pin4= ");
          Serial.print(R2[i]);
        }        
        // BMW Water Sensor
        else if (i==5){
          R2[i]=-.09459*R2[i]+183.8406;
          Serial.print(", H2O= ");
          Serial.print(R2[i]);
        }
        //catch all
        else {
           Serial.print(", R2[");Serial.print(i);Serial.print("] = ");
           Serial.print(R2[i]);
        }
        
#if RAW_OUT
        Serial.print('(');Serial.print(raw[i]);Serial.print(')');
#endif //RAW_OUT
       
        logfile.print(Vout[i]);
        logfile.print(',');
        logfile.print(R2[i]);
        }
      
    }
    if (outputIt){
      logfile.print(",");
    }
  }

  // -- add hall sensor reading
  logfile.print(',');
  logfile.print(rpm);
  Serial.print(", RPM = ");
  Serial.print(rpm,DEC);
  // -- end hall sensor
  if (outputIt) {
    Serial.print("\n");
    logfile.println();
  }
}

void outputDate(void)
{
  DateTime now;
  
  // log milliseconds since starting
  uint32_t m = millis();
  logfile.print(m);           // milliseconds since start
  logfile.print(',');    
#if ECHO_TO_SERIAL
  Serial.print(m);         // milliseconds since start
  Serial.print(", ");  
#endif

  // fetch the time
  now = RTC.now();
  // log time
  logfile.print(now.unixtime()); // seconds since 1/1/1970
  logfile.print(',');
  logfile.print('"');
  logfile.print(now.year(), DEC);
  logfile.print("/");
  logfile.print(now.month(), DEC);
  logfile.print("/");
  logfile.print(now.day(), DEC);
  logfile.print(" ");
  logfile.print(now.hour(), DEC);
  logfile.print(":");
  logfile.print(now.minute(), DEC);
  logfile.print(":");
  logfile.print(now.second(), DEC);
  logfile.print('"');
  logfile.print(',');
#if ECHO_TO_SERIAL
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
#endif //ECHO_TO_SERIAL
}

void loop() {


// -- hall sensor
   if (half_revolutions >= 20) { 
     //Update RPM every 20 counts, increase this for better RPM resolution,
     //decrease for faster update
     rpm = 30*LOG_INTERVAL/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
    // Serial.println(rpm,DEC);
   }
// -- hall sensor end



  
    // delay for the amount of time we want between readings
  delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));
  outputDate();
  readAnalogs(true);


  // Now we write data to disk! Don't sync too often - requires 2048 bytes of I/O to SD card
  // which uses a bunch of power and takes time
  if ((millis() - syncTime) < SYNC_INTERVAL) return;
  syncTime = millis();
  
  // blink LED to show we are syncing data to the card & updating FAT!
  logfile.flush();
}


// -- hall sensor
 void rpm_fun()
 {
   half_revolutions++;
   //Each rotation, this interrupt function is run twice
 }
// -- hall sensor end
