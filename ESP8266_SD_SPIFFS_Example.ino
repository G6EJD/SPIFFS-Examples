// Example of using the Serial Data Card Filing System
#define FS_NO_GLOBALS //allow spiffs to coexist with SD card, define BEFORE including FS.h
#include <FS.h> //spiff file system
#include "SD.h";
//#define SD_MODE

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  #ifdef SD_MODE
    if (!SD.begin(D8)) Serial.println("initialization failed!");
  #else
    SPIFFS.begin();
  #endif
}

void loop() {
  // Assign a file name e.g. 'names.dat' or 'data.txt' or 'data.dat' try to use the 8.3 file naming convention format could be 'data.d'
  char filename [] = "datalog.txt";                     // Assign a filename or use the format e.g. SD.open("datalog.txt",...);

  #ifdef SD_MODE
    if (SD.exists(filename)) SD.remove(filename);         // First in this example check to see if a file already exists, if so delete it
    File myDataFile = SD.open(filename, FILE_WRITE);    // Open a file for reading and writing (appending)
  #else
    if (SPIFFS.exists(filename)) SPIFFS.remove(filename);         // First in this example check to see if a file already exists, if so delete it
    fs::File myDataFile = SPIFFS.open(filename, "a+");          // Open a file for reading and writing (appending)
  #endif
  
  if (!myDataFile)Serial.println("file open failed");   // Check for errors
  
  myDataFile.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");     // Write some data to it (26-characters)
  myDataFile.println(3.141592654);
  Serial.println(myDataFile.size());                    // Display the file size (26 characters + 4-byte floating point number + 6 termination bytes (2/line) = 34 bytes)
  myDataFile.close();                                   // Close the file

  #ifdef SD_MODE
    myDataFile = SD.open(filename, FILE_READ);    // Open a file for reading and writing (appending)
  #else
    myDataFile = SPIFFS.open(filename, "r");          // Open a file for reading and writing (appending)
  #endif
  if (!myDataFile) Serial.println("file open failed");  // Check for errors
  while (myDataFile.available()) {
    Serial.write(myDataFile.read());                    // Read all the data from the file and display it
  }
  myDataFile.close();                                   // Close the file
  delay(10000);                                         // wait and then do it all again
}

