
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
  for (auto& hotspot : hotspots) {
     const char* ssidSample = hotspot["ssid"];
     const char* passwordSample = hotspot["password"];
     Serial.println("ssid:");
     Serial.println(ssidSample);
     Serial.println("password:");
     Serial.println(passwordSample);
  }

  return true;
}
