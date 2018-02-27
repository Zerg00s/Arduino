
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

  // Real world application would store these values in some variables for
  // later use.

  Serial.print("Loaded name: ");
  Serial.println(sName);

  JsonArray& hotspots = jsonConfig["hotspots"];
  int i = 0;
  for (auto& hotspot : hotspots) {
     
     String ssidSample = hotspot["ssid"];
     String passwordSample = hotspot["password"];
     Serial.println("ssid:");
     Serial.println(ssidSample);
     Serial.println("password:");
     Serial.println(passwordSample);
     Hotspot h;
     h.ssid = string2char(ssidSample);
     h.password = string2char(passwordSample);
     hot_spots[i] = h;
     i++;
     
  }

  return true;
}

char* string2char(String str){
    char * writable = new char[str.length() + 1];
    std::copy(str.begin(), str.end(), writable);
    writable[str.length()] = '\0'; // don't forget the terminating 0
    return writable;
    // TODO:  don't forget to free the string after using it
    // delete[] writable;
}
