#include "plottingpage.h"
#include "indexpage.h"
#include "viewpage.h"
#include "data.h"
#include "graph.h"
#include "kml.h"

#define __DEBUG__

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
//#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SD.h>

#ifndef APSSID
#define APSSID "GPS-AP"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;

ESP8266WebServer server(80);

uint32_t minSats = 2;
TinyGPSPlus gps;

// SD (SPI) - recomendado en D1 mini
#define SD_SCK_PIN  D5   // GPIO14
#define SD_MISO_PIN D6   // GPIO12
#define SD_MOSI_PIN D7   // GPIO13
#define SD_CS_PIN   D8   // GPIO15

// GPS por UART hardware
#define GPS_RX0_PIN RX  // GPIO3
#define GPS_TX0_PIN TX  // GPIO1

hd44780_I2Cexp lcd;

gpsData gpsD;

String archivo = "";
String linea = "";

TinyGPSCustom pdop(gps, "GNGSA", 15); // $GPGSA sentence, 15th element
TinyGPSCustom hdop(gps, "GNGSA", 16); // $GPGSA sentence, 16th element
TinyGPSCustom vdop(gps, "GNGSA", 17); // $GPGSA sentence, 17th element

/*IP por defecto para acceder por navegador http://192.168.4.1 */
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  //ss.begin(9600);
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(20,4);

  //Serial.print("Configuring access point...");
  /* Sin el parametro de password, deja al AP libre de acceso */
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
  //Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/read",  genJson);
  server.on("/start", handleStart);     
  server.on("/plot", handlePlot);       
  server.on("/view", handleView);       
  server.on("/save", handleSave);  

  server.begin();
  //Serial.println("HTTP server started");
  
  SPI.begin();
  if (!SD.begin(SD_CS_PIN)) {
    // manejo de error: encender un LED
  }

}

void handleRoot() {
  server.send(200, "text/html", indexpage);
}

void genJson()
{
  StaticJsonDocument<130> doc;
  doc["lat"] = gpsD.latitud;
  doc["long"] = gpsD.longitud;
  doc["alt"] = gpsD.alt;
  doc["sats"] = gpsD.sats;
  doc["hdop"] = gpsD.hdop;
  doc["dateTime"] = gpsD.dateTime;

  char json[120];
  serializeJson(doc, json, sizeof(json));

  //Serial.println(json);
  server.send(200, "text/json", json);
}

void loop() {
  server.handleClient();
  genGPSData();
}

void handleView() {
  server.send_P(200, "text/html", viewpage);
}

String sanitizeFilename(String name) {
  name.trim();
  String out = "";
  for (size_t i = 0; i < name.length(); i++) {
    char c = name[i];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.') {
      out += c;
    } else if (c == ' ') {
      out += '_';
    }
  }

  if (out.length() == 0) {
    return "";
  }

  if (!out.endsWith(".txt")) {
    out += ".txt";
  }

  return out;
}

int readLastPointId(const String &path) {
  File f = SD.open(path, "r");
  if (!f) {
    return 1;
  }

  String lastLine = "";
  while (f.available()) {
    String line = f.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      lastLine = line;
    }
  }
  f.close();

  if (lastLine.length() == 0) {
    return 1;
  }

  int sep = lastLine.indexOf(';');
  if (sep <= 0) {
    return 1;
  }

  int lastId = lastLine.substring(0, sep).toInt();
  if (lastId < 1) {
    return 1;
  }

  return lastId + 1;
}

void handlePlot() {
  if (!server.hasArg("file")) {
    server.send_P(400, "text/plain", "Missing file");
    return;
  }
  String rawName = server.arg("file");
  String cleanName = sanitizeFilename(rawName);
  if (cleanName.length() == 0) {
    server.send_P(400, "text/plain", "Invalid file");
    return;
  }
  archivo = "/" + cleanName;
  int nextPointId = 1;
  if (!SD.exists(archivo)) {
    File f = SD.open(archivo, "w");
    if (f) {
      f.close();
    } else {
      server.send_P(500, "text/plain", "File error");
      return;
    }
  } else {
    nextPointId = readLastPointId(archivo);
  }
  String page = FPSTR(plottpage);
  page.replace("%POINTID%", String(nextPointId));
  server.send(200, "text/html", page);
}

void handleStart() {
  server.send_P(200, "text/html", startpage);
}

/* Manejo del request para que guarde los datos*/
void handleSave() {
  if (!server.hasArg("point")) {
    server.send(400, "text/plain", "Missing point");
    return;
  }

  int pointID = server.arg("point").toInt();
  String linea = "";

  // id de linea
  linea = String(pointID) + ";";
  // latitud
  linea += String(gpsD.latitud,8) + ";";
  // longitud
  linea += String(gpsD.longitud,8) + ";";
  // altura
  linea += String(gpsD.alt, 1) + ";";
  // cantidad de satelites
  linea += String(gpsD.sats) + ";";
  // hdop
  linea += String(gpsD.hdop, 2) + ";";
  // fecha y hora
  linea += gpsD.dateTime + ";";
  linea += "\n";

  // Enviar a consola
  /*Serial.println("SAVE:");
  Serial.println(linea);*/

  if (archivo.length() == 0) {
    server.send(400, "text/plain", "Sin nombre de archivo");
    return;
  }

  File f = SD.open(archivo, "a");
  if (!f) {
    //Serial.println("ERROR: No se pudo abrir archivo");
    server.send_P(500, "text/plain", "File error");
    return;
  }
  f.print(linea);
  f.close();  

  rebuildKmlFromTxt(archivo);

  // Usar últimos datos GPS ya validados
  // Guardar en archivo (luego lo implemento)

  server.send(200, "text/plain", "OK");
}


void genGPSData()
{
  if (gps.altitude.isUpdated() || gps.satellites.isUpdated() ||
    pdop.isUpdated() || hdop.isUpdated() || vdop.isUpdated())
  { 
    if(gps.satellites.value() > minSats)    
    {
      digitalWrite(13, HIGH);
      gpsD.latitud = gps.location.lat();
      gpsD.longitud = gps.location.lng();
      gpsD.sats = gps.satellites.value();
      gpsD.alt = gps.altitude.meters();
      gpsD.hdop = gps.hdop.hdop();
      gpsD.dateTime = genDate() + "  " + genTime();
 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LAT:  " + String(gpsD.latitud,8));
      lcd.setCursor(0, 1);
      lcd.print("LONG: " + String(gpsD.longitud,8));
      lcd.setCursor(0, 2);
      lcd.print("S:" + String(gpsD.sats));
      lcd.setCursor(5, 2);
      lcd.print("H:" + String(gpsD.hdop));
      lcd.setCursor(12, 2);
      lcd.print("A:" + String(gpsD.alt) );
      lcd.setCursor(0, 3);
      lcd.print(gpsD.dateTime);
      
    } else {
      digitalWrite(13, LOW);
      //Serial.println("Low sats: " + String(gps.satellites.value()));
      lcd.clear();
      lcd.print("Low sats");
    }
  }

  while (Serial.available() > 0)
  {
    gps.encode(Serial.read());
  }
 
}

/*
void printSerialGPS()
{
  Serial.println();
  Serial.print("Lat: " + String(gps.location.lat(), 6));
  Serial.print(" | ");    
  Serial.print("Long: " + String(gps.location.lng(), 6));
  Serial.print(" | ");    
  Serial.print("Sats: " + String(gps.satellites.value()));
  Serial.print(" | ");    
  Serial.print("Alt: ") + String(gps.altitude.meters(), 0);
  Serial.print(" | ");    
  Serial.print("HDOP: ") + String(gps.hdop.hdop(), 2);
  Serial.print(" | ");    
  Serial.print("Date: " + genDate());
  Serial.print(" | ");    
  Serial.print("Time: " + genTime());
}
*/

String genDate()
{

  String str;

  if (gps.date.isValid())
  {
    str = String(gps.date.day());
    str = str + F("/");
    if(gps.date.month() < 10)
    {
      str = str + "0" + String(gps.date.month());
    } 
    else
    {
      str = str + String(gps.date.month());
    }
    str = str + F("/");
    str = str + String(gps.date.year());
  } else {
    str = str + "No date";
  }
  return str;
}

String genTime()
{
  String str;
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) str = F("0");
    str = str + String((gps.time.hour())) + ":";

    if (gps.time.minute() < 10) str = str + F("0");
    str = str + String(gps.time.minute()) + F(":");
    
    if (gps.time.second() < 10) str = str + F("0");
    str = str + String(gps.time.second());

  }  else {
    str = str + "No time";
  }
  return str;
}
