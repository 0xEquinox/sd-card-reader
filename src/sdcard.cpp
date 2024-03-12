#include "sdcard.hpp"
#include "vector.hpp"

void listFiles(String dirPath) {
  // Open the directory
  File dir = SD.open(dirPath);
  
  // Check if the directory opened successfully
  if (!dir) {
    Serial.println("Failed to open directory");
    return;
  }
  
  // Print header
  Serial.println("Files in directory: " + dirPath);
  
  // Loop through each file in the directory
  while (File file = dir.openNextFile()) {
    // Print the filename
    Serial.println(file.name());
    // Close the file
    file.close();
  }
  
  // Close the directory
  dir.close();
}

void readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

int fileCount = 0;

void listAudioFiles(String dirPath, StringList fileList) {
  // Open the directory
  File dir = SD.open(dirPath);

  // Check if the directory opened successfully
  if (!dir) {
    return;
  }
  // Loop through each file in the directory
  while (File file = dir.openNextFile()) {
    String fileName = file.name();
    // Check if the file has a supported audio extension
    if (fileName.endsWith(".mp3") || fileName.endsWith(".wav") || fileName.endsWith(".flac")) {
      // Add the file to the list
      fileList.add(fileName);
    }
    // Close the file
    file.close();
  }
  // Close the directory
  dir.close();

  // Return the pointer to the array
}