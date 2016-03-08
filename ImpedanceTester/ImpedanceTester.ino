
// Sensor reader
int analogPins[6]= {0,1,2,3,4,5};
int raw[6]= {0};
int Vin= 5;
float Vout[6]= {0};
float R1[6]= {10000,10000,10000,10000,10000,10000};
float R2[6]= {0};
float buffer[6]= {0};

int timeInterval = 1000;//in msec
int timeSinceStart = 0;


void setup() {
  Serial.begin(9600);
}

void readAnalogs(bool outputIt){
  if (outputIt) Serial.print("Time ");Serial.print(timeSinceStart);

  //Read in all 6 inputs, no way to read multiple at once, 
  // so do it one at a time
  for (int i=0;i<6;i++){
    raw[i]=analogRead(analogPins[i]);
    if(raw[i]) {
      buffer[i]= raw[i] * Vin;
      Vout[i]= (buffer[i])/1024.0;
      buffer[i]= (Vin/Vout[i]) -1;
      R2[i]= R1[i] * buffer[i];
      if (outputIt){
        Serial.print(" Vout[");Serial.print(i);Serial.print("] = ");
        Serial.print(Vout[i]);
        Serial.print(" R2[");Serial.print(i);Serial.print("] = ");
        Serial.print(R2[i]);
      }
    } 
  }
  if (outputIt) Serial.print("\n");
}

void loop() {
  readAnalogs(true);
  delay(timeInterval);
  timeSinceStart++;
}
