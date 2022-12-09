#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>

#define RE 8
#define DE 7
#define RE1 9
#define DE1 10

const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

const byte humdt[] = {0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0X25, 0xCA};

byte values[11];
byte values1[11];

SoftwareSerial mod(2, 3);
SoftwareSerial mod1(5, 4);

byte val1, val2, val3, val4, val5, val6;
String Request;

int hum;
float temp;                 // Stores temperature value
const int AirValue = 620;   // you need to replace this value with Value_1
const int WaterValue = 310; // you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

String DeviceId = "EA/DW/004";

byte nitrogen()
{
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(nitro, sizeof(nitro)) == 8)
  {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++)
    {
      // Serial.print(mod.read(),HEX);
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte phosphorous()
{
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(phos, sizeof(phos)) == 8)
  {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++)
    {
      // Serial.print(mod.read(),HEX);
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte potassium()
{
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(pota, sizeof(pota)) == 8)
  {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++)
    {
      // Serial.print(mod.read(),HEX);
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte humidity()
{
  digitalWrite(DE1, HIGH);
  digitalWrite(RE1, HIGH);
  delay(10);
  if (mod1.write(humdt, sizeof(humdt)) == 8)
  {
    digitalWrite(DE1, LOW);
    digitalWrite(RE1, LOW);
    for (byte i = 0; i < 11; i++)
    {
      // Serial.print(mod1.read(),HEX);
      values1[i] = mod1.read();
      Serial.print(values1[i], HEX);
    }
    Serial.println();
  }
  return values1[4];
}

void setup()
{
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  pinMode(RE1, OUTPUT);
  pinMode(DE1, OUTPUT);
  Serial.begin(9600);
  mod.begin(9600);
}

void loop()
{
  val3 = nitrogen();
  delay(500);
  val4 = phosphorous();
  delay(500);
  val5 = potassium();
  delay(500);
  val6 = humidity();
  delay(500);

  Serial.print("Nitrogen: ");
  Serial.print(val3);
  Serial.println(" mg/kg");
  Serial.print("Phosphorous: ");
  Serial.print(val4);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(val5);
  Serial.println(" mg/kg");

  Serial.print(float(val6) / 10);
  Serial.println(" g.m-3 %");
}