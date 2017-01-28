// Example of using the Serial Data Card Filing System

#include <SD.h>;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  if (!SD.begin(D8)) Serial.println("initialization failed!");
}

void loop() {
  // Assign a file name e.g. 'names.dat' or 'data.txt' or 'data.dat' try to use the 8.3 file naming convention format could be 'data.d'
  char filename [] = "datalog.txt";                     // Assign a filename or use the format e.g. SD.open("datalog.txt",...);

  if (SD.exists(filename)) SD.remove(filename);         // First in this example check to see if a file already exists, if so delete it
  File myDataFile = SD.open(filename, FILE_WRITE);      // Open a file for reading and writing (appending)
  if (!myDataFile)Serial.println("file open failed");   // Check for errors
  
  myDataFile.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");     // Write some data to it (26-characters)
  myDataFile.println(3.141592654);
  Serial.println(myDataFile.size());                    // Display the file size (26 characters + 4-byte floating point number + 6 termination bytes (2/line) = 34 bytes)
  myDataFile.close();                                   // Close the file

  myDataFile = SD.open(filename, FILE_READ);              // Open the file again, this time for reading
  if (!myDataFile) Serial.println("file open failed");  // Check for errors
  while (myDataFile.available()) {
    Serial.write(myDataFile.read());                    // Read all the data from the file and display it
  }
  myDataFile.close();                                   // Close the file
  delay(10000);                                         // wait and then do it all again
}
