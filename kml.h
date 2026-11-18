#pragma once

#include <Arduino.h>
#include <SD.h>

String kmlPathFromTxt(const String &txtPath);
void kmlWriteHeader(File &kml, const String &name);
void kmlWriteFooter(File &kml);
void rebuildKmlFromTxt(const String &txtPath);
