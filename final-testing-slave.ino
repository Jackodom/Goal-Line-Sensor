#include <VL53L1X.h>

int distance = 0;
bool starting = true;
int averageDistance = 1800;

const uint8_t sensorCount = 3;
const uint8_t xshutPins[sensorCount] = { 2,3,4 };

VL53L1X sensors[sensorCount];

void clear(){
  while(Serial.available() > 0)
  {
    Serial.read();
  }
}


void initialize(){
   for (uint8_t i = 0; i < sensorCount; i++) {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }

  // Enable, initialize, and start each sensor, one by one.
  for (uint8_t i = 0; i < sensorCount; i++) {
    pinMode(xshutPins[i], INPUT);
    delay(10);

    sensors[i].setTimeout(500);
    if (!sensors[i].init()) {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
    }
    sensors[i].setAddress(0x2A + i);
    sensors[i].setDistanceMode(VL53L1X::Short);
    sensors[i].setROISize(4, 4);
    sensors[i].setROICenter(199);
    sensors[i].startContinuous(50);
}
}
void analyzeReading(int i)  // Pass 'i' from the loop
{
  String cipher = "";
  char letters[10] = {'A','B', 'C', 'D', 'E', 'F', 'G','H','I','J'};

  long distance = sensors[i].read();  // Read distance for the current sensor
    if ((distance + 150) < averageDistance)
    {
      delay(100);
      long checkDistance = sensors[i].read();
      if ((checkDistance + 150) < averageDistance) 
      {
        cipher += "I";
      }
      else
      {
        cipher += "G";
      }
      cipher += letters[(distance / 1000)];
      cipher += letters[(distance % 1000) / 100];
      cipher += letters[(distance % 100) / 10];
      cipher += letters[i];

      send(cipher);
    }
}

void recieve()
{
  char input[50];
  while(Serial.available() > 0 )
    {
      Serial.readBytes(input,50);
    }
  String rec;
  rec = String(input);
  char firstLetter = rec.charAt(0);
}

void send(String send)
{
    int send_len = send.length() +1;
    char char_array[send_len];
    send.toCharArray(char_array, send_len);
    Serial.write(char_array, send_len);
}

void setup() 
{
  Serial.begin(115200);
  initialize();
}

void loop() {
  for (uint8_t i = 0; i < sensorCount; i++) 
    { 
      analyzeReading(i);
    }
}

