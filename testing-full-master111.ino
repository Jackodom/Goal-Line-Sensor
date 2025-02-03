#include <SoftwareSerial.h>
bool confirm = false;
bool starting = true;
int distance = 0;
int goalSensorCount = 0;
int interfereSensorCount = 0;
int interDistance = 0;
int goalDistance = 0;
int sensor = 0;
int processor = 0;

SoftwareSerial nano1( 6,7 );
SoftwareSerial nano2( 8, 9);
SoftwareSerial nano3( 10,11 );
SoftwareSerial nano4( 12, 13);
SoftwareSerial nano5( 5,4 );
SoftwareSerial nano6( 3,2 );
SoftwareSerial* nanos[6] = { &nano2, &nano3, &nano1,  &nano4, &nano5, &nano6 };

void visualOutput()
{
  Serial.println(F("Checking Goal..."));
  Serial.println(F("last goal detection."));
  char positions[12][18] = {
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
  };
  positions[(interDistance / 150)][interfereSensorCount] = 'O';
  positions[(goalDistance / 150)][goalSensorCount] = 'x';
  Serial.println(F("           - - - - - - - - - - - - - - - - - - - - - - - - -Top Bar - - - - - - - - - - - - - - - - - - - - - - - - - - -"));
  Serial.print(F(" "));
  for (int i = 0; i < 12; i++) 
  {
    Serial.print((i + 1) * 6);
    Serial.print(" Inches:");
    for (int j = 0; j < 18; j++) 
    {
      Serial.print("|  ");
      Serial.print(positions[i][j]);
      Serial.print(" |");
    }
    Serial.println(" ");
  }
  Serial.println(F("Press red button on uno to restart"));
  while(true){}
}

void send(String send)
{
    int send_len = send.length() +1;
    char char_array[send_len];
    send.toCharArray(char_array, send_len);
    Serial.write(char_array, send_len);
}
  void convertString(String rec, int i)
  {
    String letters = "ABCDEFGHIJ";
    int num = 0;
    num += letters.indexOf(rec.charAt(1)) * 1000;
    num += letters.indexOf(rec.charAt(2)) * 100;
    num += letters.indexOf(rec.charAt(3)) * 10;
    if(rec.charAt(0) == 'G')
    {
      Serial.println("goal");
      goalSensorCount = (i+1) * 3;
      goalDistance = num;
      Serial.print(goalDistance);
      visualOutput();
    }
    else if(rec.charAt(0) == 'I')
    {
      interfereSensorCount = (i+1) * 3;
      interDistance = num;
      Serial.println("Interference");
    }
  }

  void recieve(int i)
{
  char input[4];
  nanos[i]->readBytes(input,6);   
  String rec;
  rec = String(input);
  char firstLetter = rec.charAt(0);
  if(firstLetter == 'G' || firstLetter == 'I')
  {
    convertString(rec, i);
  }
}

void setup() 
{
  Serial.begin(115200);
  nano1.begin(115200);
  nano2.begin(115200);
  nano3.begin(115200);
  nano4.begin(115200);
  nano5.begin(115200);
  nano6.begin(115200);
}

void loop() 
{
   for(int i = 0; i < 6; i++)
   {
       recieve(i);
   }
}
