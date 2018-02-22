const char* ssid = "ESP 8266";
const char* password = "welcomehome";
ESP8266WebServer server(80);
bool serverMode = false;
File fsUploadFile;              // a File object to temporarily store the received file

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}


void InitializeWifiAP(){
  serverMode = true;
  //AP == access point
  // STA  - station mode
  //ESP8266 Wi-Fi Modes: Station vs. Access Point Using Arduino IDE:
  //https://www.youtube.com/watch?v=uFjWKhScnVY
  WiFi.mode(WIFI_AP);
  // STA - means our 8266 will just connect to WIFI
  // AP - means our 8266 is a standalone server that other devices will connect to
  // AP_STA - means we are doing both modes
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");  
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/SetWifiSpot", SetWifiSpot);
  server.on("/StopWifiSpot", StopWifiSpot);

  server.on("/upload", HTTP_GET, []() {                 // if the client requests the upload page
    if (!handleFileRead("/upload.html"))                // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });

  server.on("/upload", HTTP_POST,                       // if the client posts to the upload page
    [](){ server.send(200); },                          // Send status 200 (OK) to tell the client we are ready to receive
    handleFileUpload                                    // Receive and save the file
  );

  server.onNotFound([]() {                              // If the client requests any URI
    if (!handleFileRead(server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  server.begin();
  Serial.println("HTTP server started");

  
  while(serverMode){
    server.handleClient();
  }
}

void SetWifiSpot(){
  String received_ssid = server.arg("ssid"); 
  String received_password = server.arg("password");
  Serial.print("SSID: ");
  Serial.println(received_ssid);
  Serial.print("Password: ");
  Serial.println(received_password);
  server.send(200, "text/html", "<h1>"+received_ssid+" saved</h1>");
}

void StopWifiSpot(){
  server.send(200, "text/html", "<h1>Wifi Hotspot stopped</h1>");
  WiFi.disconnect(); 
  serverMode = false;
}


 
bool handleFileRead(String path){  // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";           // If a folder is requested, send the index file
  String contentType = getContentType(path);             // Get the MIME type
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){  // If the file exists, either as a compressed archive, or normal
    if(SPIFFS.exists(pathWithGz))                          // If there's a compressed version available
      path += ".gz";                                         // Use the compressed version
    File file = SPIFFS.open(path, "r");                    // Open the file
    size_t sent = server.streamFile(file, contentType);    // Send it to the client
    file.close();                                          // Close the file again
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);
  return false;                                          // If the file doesn't exist, return false
}


void handleFileUpload(){ // upload a new file to the SPIFFS
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    if(!filename.startsWith("/")) filename = "/"+filename;
    Serial.print("handleFileUpload Name: "); Serial.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
    filename = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile) {                                    // If the file was successfully created
      fsUploadFile.close();                               // Close the file again
      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
      server.sendHeader("Location","/success.html");      // Redirect the client to the success page
      server.send(303);
    } else {
      server.send(500, "text/plain", "500: couldn't create file");
    }
  }
}



String getContentType(String filename){
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}


//var xhr = new XMLHttpRequest();
//xhr.open('post', '/setWifiSpot');
//xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
//xhr.send('ssid="Denis-wifi"&password="welcomehome"');

