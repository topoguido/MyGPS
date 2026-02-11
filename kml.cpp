#include "kml.h"

String kmlPathFromTxt(const String &txtPath) {
  int dot = txtPath.lastIndexOf('.');
  if (dot > 0) {
    return txtPath.substring(0, dot) + ".kml";
  }
  return txtPath + ".kml";
}

String indexToLetters(int index) {
  if (index < 1) {
    return "";
  }

  String out = "";
  while (index > 0) {
    index -= 1;
    char c = 'A' + (index % 26);
    out = String(c) + out;
    index /= 26;
  }

  return out;
}

void kmlWriteHeader(File &kml, const String &name) {
  kml.println(F("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"));
  kml.println(F("<kml xmlns=\"http://www.opengis.net/kml/2.2\">"));
  kml.println(F("  <Document>"));
  kml.print(F("    <name>"));
  kml.print(name);
  kml.println(F("</name>"));
  kml.println(F("    <description/>"));
  kml.println(F("    <Style id=\"icon-1899-0288D1-nodesc-normal\">"));
  kml.println(F("      <IconStyle>"));
  kml.println(F("        <color>ffd18802</color>"));
  kml.println(F("        <scale>1</scale>"));
  kml.println(F("        <Icon>"));
  kml.println(F("          <href>https://www.gstatic.com/mapspro/images/stock/503-wht-blank_maps.png</href>"));
  kml.println(F("        </Icon>"));
  kml.println(F("        <hotSpot x=\"32\" xunits=\"pixels\" y=\"64\" yunits=\"insetPixels\"/>"));
  kml.println(F("      </IconStyle>"));
  kml.println(F("      <LabelStyle>"));
  kml.println(F("        <scale>0</scale>"));
  kml.println(F("      </LabelStyle>"));
  kml.println(F("      <BalloonStyle>"));
  kml.println(F("        <text><![CDATA[<h3>$[name]</h3>]]></text>"));
  kml.println(F("      </BalloonStyle>"));
  kml.println(F("    </Style>"));
  kml.println(F("    <Style id=\"icon-1899-0288D1-nodesc-highlight\">"));
  kml.println(F("      <IconStyle>"));
  kml.println(F("        <color>ffd18802</color>"));
  kml.println(F("        <scale>1</scale>"));
  kml.println(F("        <Icon>"));
  kml.println(F("          <href>https://www.gstatic.com/mapspro/images/stock/503-wht-blank_maps.png</href>"));
  kml.println(F("        </Icon>"));
  kml.println(F("        <hotSpot x=\"32\" xunits=\"pixels\" y=\"64\" yunits=\"insetPixels\"/>"));
  kml.println(F("      </IconStyle>"));
  kml.println(F("      <LabelStyle>"));
  kml.println(F("        <scale>1</scale>"));
  kml.println(F("      </LabelStyle>"));
  kml.println(F("      <BalloonStyle>"));
  kml.println(F("        <text><![CDATA[<h3>$[name]</h3>]]></text>"));
  kml.println(F("      </BalloonStyle>"));
  kml.println(F("    </Style>"));
  kml.println(F("    <StyleMap id=\"icon-1899-0288D1-nodesc\">"));
  kml.println(F("      <Pair>"));
  kml.println(F("        <key>normal</key>"));
  kml.println(F("        <styleUrl>#icon-1899-0288D1-nodesc-normal</styleUrl>"));
  kml.println(F("      </Pair>"));
  kml.println(F("      <Pair>"));
  kml.println(F("        <key>highlight</key>"));
  kml.println(F("        <styleUrl>#icon-1899-0288D1-nodesc-highlight</styleUrl>"));
  kml.println(F("      </Pair>"));
  kml.println(F("    </StyleMap>"));
  kml.println(F("    <Style id=\"line-000000-2000-nodesc-normal\">"));
  kml.println(F("      <LineStyle>"));
  kml.println(F("        <color>ff000000</color>"));
  kml.println(F("        <width>2</width>"));
  kml.println(F("      </LineStyle>"));
  kml.println(F("      <BalloonStyle>"));
  kml.println(F("        <text><![CDATA[<h3>$[name]</h3>]]></text>"));
  kml.println(F("      </BalloonStyle>"));
  kml.println(F("    </Style>"));
  kml.println(F("    <Style id=\"line-000000-2000-nodesc-highlight\">"));
  kml.println(F("      <LineStyle>"));
  kml.println(F("        <color>ff000000</color>"));
  kml.println(F("        <width>3</width>"));
  kml.println(F("      </LineStyle>"));
  kml.println(F("      <BalloonStyle>"));
  kml.println(F("        <text><![CDATA[<h3>$[name]</h3>]]></text>"));
  kml.println(F("      </BalloonStyle>"));
  kml.println(F("    </Style>"));
  kml.println(F("    <StyleMap id=\"line-000000-2000-nodesc\">"));
  kml.println(F("      <Pair>"));
  kml.println(F("        <key>normal</key>"));
  kml.println(F("        <styleUrl>#line-000000-2000-nodesc-normal</styleUrl>"));
  kml.println(F("      </Pair>"));
  kml.println(F("      <Pair>"));
  kml.println(F("        <key>highlight</key>"));
  kml.println(F("        <styleUrl>#line-000000-2000-nodesc-highlight</styleUrl>"));
  kml.println(F("      </Pair>"));
  kml.println(F("    </StyleMap>"));
  kml.println(F("    <Style id=\"poly-1A237E-2000-23-nodesc-normal\">"));
  kml.println(F("      <LineStyle>"));
  kml.println(F("        <color>ff7e231a</color>"));
  kml.println(F("        <width>2</width>"));
  kml.println(F("      </LineStyle>"));
  kml.println(F("      <PolyStyle>"));
  kml.println(F("        <color>177e231a</color>"));
  kml.println(F("        <fill>1</fill>"));
  kml.println(F("        <outline>1</outline>"));
  kml.println(F("      </PolyStyle>"));
  kml.println(F("      <BalloonStyle>"));
  kml.println(F("        <text><![CDATA[<h3>$[name]</h3>]]></text>"));
  kml.println(F("      </BalloonStyle>"));
  kml.println(F("    </Style>"));
  kml.println(F("    <Style id=\"poly-1A237E-2000-23-nodesc-highlight\">"));
  kml.println(F("      <LineStyle>"));
  kml.println(F("        <color>ff7e231a</color>"));
  kml.println(F("        <width>3</width>"));
  kml.println(F("      </LineStyle>"));
  kml.println(F("      <PolyStyle>"));
  kml.println(F("        <color>177e231a</color>"));
  kml.println(F("        <fill>1</fill>"));
  kml.println(F("        <outline>1</outline>"));
  kml.println(F("      </PolyStyle>"));
  kml.println(F("      <BalloonStyle>"));
  kml.println(F("        <text><![CDATA[<h3>$[name]</h3>]]></text>"));
  kml.println(F("      </BalloonStyle>"));
  kml.println(F("    </Style>"));
  kml.println(F("    <StyleMap id=\"poly-1A237E-2000-23-nodesc\">"));
  kml.println(F("      <Pair>"));
  kml.println(F("        <key>normal</key>"));
  kml.println(F("        <styleUrl>#poly-1A237E-2000-23-nodesc-normal</styleUrl>"));
  kml.println(F("      </Pair>"));
  kml.println(F("      <Pair>"));
  kml.println(F("        <key>highlight</key>"));
  kml.println(F("        <styleUrl>#poly-1A237E-2000-23-nodesc-highlight</styleUrl>"));
  kml.println(F("      </Pair>"));
  kml.println(F("    </StyleMap>"));
  kml.println(F("    <Folder>"));
  kml.println(F("      <name>Puntos</name>"));
}

void kmlWriteFooter(File &kml) {
  kml.println(F("  </Document>"));
  kml.println(F("</kml>"));
}

void rebuildKmlFromTxt(const String &txtPath) {
  String kmlPath = kmlPathFromTxt(txtPath);

  File txt = SD.open(txtPath, "r");
  if (!txt) {
    return;
  }

  File kml = SD.open(kmlPath, "w");
  if (!kml) {
    txt.close();
    return;
  }

  kmlWriteHeader(kml, txtPath);

  String coords = "";
  String firstCoord = "";
  String firstLat = "";
  String firstLon = "";
  String firstLabel = "";

  while (txt.available()) {
    String line = txt.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) {
      continue;
    }

    int p1 = line.indexOf(';');
    int p2 = line.indexOf(';', p1 + 1);
    int p3 = line.indexOf(';', p2 + 1);

    if (p1 < 0 || p2 < 0 || p3 < 0) {
      continue;
    }

    String id = line.substring(0, p1);
    String lat = line.substring(p1 + 1, p2);
    String lon = line.substring(p2 + 1, p3);
    String label = indexToLetters(id.toInt());
    if (label.length() == 0) {
      label = id;
    }

    kml.println(F("      <Placemark>"));
    kml.print(F("        <name>Punto "));
    kml.print(label);
    kml.println(F("</name>"));
    kml.print(F("        <description>Lat: "));
    kml.print(lat);
    kml.print(F("; Lon: "));
    kml.print(lon);
    kml.println(F("</description>"));
    kml.println(F("        <styleUrl>#icon-1899-0288D1-nodesc</styleUrl>"));
    kml.println(F("        <Point>"));
    kml.print(F("          <coordinates>"));
    kml.print(lon);
    kml.print(",");
    kml.print(lat);
    kml.println(F(",0</coordinates>"));
    kml.println(F("        </Point>"));
    kml.println(F("      </Placemark>"));

    String coord = lon + "," + lat + ",0";
    if (firstCoord.length() == 0) {
      firstCoord = coord;
      firstLat = lat;
      firstLon = lon;
      firstLabel = label;
    }
    coords += coord + "\n";
  }

  kml.println(F("    </Folder>"));

  kml.println(F("    <Folder>"));
  kml.println(F("      <name>Perimetro</name>"));
  if (coords.length() > 0) {
    kml.println(F("      <Placemark>"));
    kml.println(F("        <name>Area sombreada</name>"));
    kml.println(F("        <styleUrl>#poly-1A237E-2000-23-nodesc</styleUrl>"));
    kml.println(F("        <Polygon>"));
    kml.println(F("          <outerBoundaryIs>"));
    kml.println(F("            <LinearRing>"));
    kml.println(F("              <tessellate>1</tessellate>"));
    kml.println(F("              <coordinates>"));
    kml.print(coords);
    kml.print(firstCoord);
    kml.println();
    kml.println(F("              </coordinates>"));
    kml.println(F("            </LinearRing>"));
    kml.println(F("          </outerBoundaryIs>"));
    kml.println(F("        </Polygon>"));
    kml.println(F("      </Placemark>"));
  }
  kml.println(F("    </Folder>"));

  kml.println(F("    <Folder>"));
  kml.println(F("      <name>Lineas</name>"));

  txt.close();
  txt = SD.open(txtPath, "r");
  if (txt) {
    String prevId = "";
    String prevLat = "";
    String prevLon = "";
    String prevLabel = "";
    int count = 0;
    while (txt.available()) {
      String line = txt.readStringUntil('\n');
      line.trim();
      if (line.length() == 0) {
        continue;
      }

      int p1 = line.indexOf(';');
      int p2 = line.indexOf(';', p1 + 1);
      int p3 = line.indexOf(';', p2 + 1);
      if (p1 < 0 || p2 < 0 || p3 < 0) {
        continue;
      }

      String id = line.substring(0, p1);
      String lat = line.substring(p1 + 1, p2);
      String lon = line.substring(p2 + 1, p3);
      String label = indexToLetters(id.toInt());
      if (label.length() == 0) {
        label = id;
      }

      if (prevId.length() > 0) {
        kml.println(F("      <Placemark>"));
        kml.print(F("        <name>Segmento "));
        kml.print(prevLabel);
        kml.print(F("-"));
        kml.print(label);
        kml.println(F("</name>"));
        kml.println(F("        <styleUrl>#line-000000-2000-nodesc</styleUrl>"));
        kml.println(F("        <LineString>"));
        kml.println(F("          <tessellate>1</tessellate>"));
        kml.println(F("          <coordinates>"));
        kml.print(F("            "));
        kml.print(prevLon);
        kml.print(F(","));
        kml.print(prevLat);
        kml.println(F(",0"));
        kml.print(F("            "));
        kml.print(lon);
        kml.print(F(","));
        kml.print(lat);
        kml.println(F(",0"));
        kml.println(F("          </coordinates>"));
        kml.println(F("        </LineString>"));
        kml.println(F("      </Placemark>"));
      }

      prevId = id;
      prevLat = lat;
      prevLon = lon;
      prevLabel = label;
      count += 1;
    }

    if (count > 1 && firstCoord.length() > 0) {
      kml.println(F("      <Placemark>"));
      kml.print(F("        <name>Segmento "));
      kml.print(prevLabel);
      kml.print(F("-"));
      kml.print(firstLabel);
      kml.println(F("</name>"));
      kml.println(F("        <styleUrl>#line-000000-2000-nodesc</styleUrl>"));
      kml.println(F("        <LineString>"));
      kml.println(F("          <tessellate>1</tessellate>"));
      kml.println(F("          <coordinates>"));
      kml.print(F("            "));
      kml.print(prevLon);
      kml.print(F(","));
      kml.print(prevLat);
      kml.println(F(",0"));
      kml.print(F("            "));
      kml.print(firstLon);
      kml.print(F(","));
      kml.print(firstLat);
      kml.println(F(",0"));
      kml.println(F("          </coordinates>"));
      kml.println(F("        </LineString>"));
      kml.println(F("      </Placemark>"));
    }
  }

  kml.println(F("    </Folder>"));

  kmlWriteFooter(kml);

  kml.close();
  txt.close();
}
