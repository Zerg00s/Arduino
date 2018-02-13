#include <ArduinoJson.h>
#include <FS.h>

// FILE SYSTEM DOCUMENTATION: http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html
// It's very well written, read it
void setup() {
  Serial.begin(9600);

  SPIFFS.begin();
  //SPIFFS.format() // Format file system
  //SPIFFS.open(path, mode) //"r", "w", "a", "r+", "w+", "a+".
  // read about all mode options here: https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm

  File f = SPIFFS.open("/f.txt", "w");
  if (!f) {
    Serial.println("file open failed");
  }

  // SPIFFS.exists(path);
  // SPIFFS.openDir(path);
  SPIFFS.remove("/log.txt");
  FSInfo fs_info;
  SPIFFS.info(fs_info);

  Serial.println(fs_info.totalBytes);
  Serial.println(fs_info.usedBytes);
  Serial.println(fs_info.usedBytes);
  Serial.println(fs_info.maxOpenFiles);
  Serial.println(fs_info.maxPathLength);


  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    Serial.print(dir.fileName());
    File f = dir.openFile("r");
    Serial.println(f.size());

    String debugLogData;
    while (f.available()) {
      debugLogData += char(f.read());
    }
    Serial.println(debugLogData);
    f.close();
  }

}

void loop() {

}
