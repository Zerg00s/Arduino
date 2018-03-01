
bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& jsonConfig = jsonBuffer.parseObject(buf.get());

  if (!jsonConfig.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }

  const char* sName = jsonConfig["name"];

  JsonArray& hotspots = jsonConfig["hotspots"];
//  int i = 0;
//  for (auto& hotspot : hotspots) {
//     
//     String ssidSample = hotspot["ssid"];
//     String passwordSample = hotspot["password"];
//     Serial.println("ssid:");
//     Serial.println(ssidSample);
//     Serial.println("password:");
//     Serial.println(passwordSample);
//     Hotspot h;
//     h.ssid = string2char(ssidSample);
//     h.password = string2char(passwordSample);
//     hot_spots[i] = h;
//     i++;
//     
//  }

  return true;
}

void LoadHotspots(){
  File hotspotsFile = SPIFFS.open("/hotspots.txt", "r");
  if (!hotspotsFile) {
    Serial.println("Failed to open hotspots.txt file");
  }
  String hotspotsAsString;
  while (hotspotsFile.available()){
    hotspotsAsString += char(hotspotsFile.read());
  }
  Hotspot h;
  h.ssid = SplitString(hotspotsAsString,'|',0);
  h.password = SplitString(hotspotsAsString,'|',1);
  hot_spots[0] = h;

  Hotspot h2;
  h2.ssid = "PAI-Mobile";
  h2.password = "Suite 500";
  hot_spots[1] = h2;
  hotspotsFile.close();

  // TODO: hotspots
  // mode = hotspotsAsString;
}

void SaveHotSpots(String newSsid, String newPassword){
    SPIFFS.remove("/hotspots.txt");
    File hotspotsFile = SPIFFS.open("/hotspots.txt", "w");
    if (!hotspotsFile) {
        Serial.print("file open failed");
    } else {
        hotspotsFile.print(newSsid+"|"+newPassword);
    }
    hotspotsFile.close();
}

void SaveBootMode(String _mode){
    SPIFFS.remove("/bootMode.json");
    File modeFile = SPIFFS.open("/bootMode.json", "w");
    if (!modeFile) {
        Serial.print("file open failed");
    } else {
        modeFile.print(_mode);
    }
    modeFile.close();
}

void LoadBootMode(){
  File modeFile = SPIFFS.open("/bootMode.json", "r");
  if (!modeFile) {
    Serial.println("Failed to open config file");
    mode = "StandardMode";
  }
  String modeSaved;
  while (modeFile.available()){
    modeSaved += char(modeFile.read());
  }
  modeFile.close();

  mode = modeSaved;
}

char* string2char(String str){
    char * writable = new char[str.length() + 1];
    std::copy(str.begin(), str.end(), writable);
    writable[str.length()] = '\0'; // don't forget the terminating 0
    return writable;
    // TODO:  don't forget to free the string after using it
    // delete[] writable;
}


String SplitString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
